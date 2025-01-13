// Copyright 2023 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/core/lib/promise/party.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/grpc.h>
#include <stdio.h>

#include <algorithm>
#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/inter_activity_latch.h"
#include "src/core/lib/promise/mpsc.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {

///////////////////////////////////////////////////////////////////////////////
// PartyTest

class PartyTest : public ::testing::Test {
 protected:
  RefCountedPtr<Party> MakeParty() {
    auto arena = SimpleArenaAllocator()->MakeArena();
    arena->SetContext<grpc_event_engine::experimental::EventEngine>(
        event_engine_.get());
    return Party::Make(std::move(arena));
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_ =
      grpc_event_engine::experimental::GetDefaultEventEngine();
};

TEST_F(PartyTest, Noop) { auto party = MakeParty(); }

TEST_F(PartyTest, CanSpawnAndRun) {
  auto party = MakeParty();
  Notification n;
  party->Spawn(
      "TestSpawn",
      [i = 10]() mutable -> Poll<int> {
        EXPECT_GT(i, 0);
        GetContext<Activity>()->ForceImmediateRepoll();
        --i;
        if (i == 0) return 42;
        return Pending{};
      },
      [&n](int x) {
        EXPECT_EQ(x, 42);
        n.Notify();
      });
  n.WaitForNotification();
}

TEST_F(PartyTest, CanSpawnWaitableAndRun) {
  auto party1 = MakeParty();
  auto party2 = MakeParty();
  Notification n;
  InterActivityLatch<void> done;
  // Spawn a task on party1 that will wait for a task on party2.
  // The party2 task will wait on the latch `done`.
  party1->Spawn(
      "party1_main",
      [&party2, &done]() {
        return party2->SpawnWaitable("party2_main",
                                     [&done]() { return done.Wait(); });
      },
      [&n](Empty) { n.Notify(); });
  ASSERT_FALSE(n.HasBeenNotified());
  party1->Spawn("party1_notify_latch", [&done]() { done.Set(); }, [](Empty) {});
  n.WaitForNotification();
}

TEST_F(PartyTest, CanSpawnFromSpawn) {
  auto party = MakeParty();
  Notification n1;
  Notification n2;
  party->Spawn(
      "TestSpawn",
      [party, &n2]() -> Poll<int> {
        party->Spawn(
            "TestSpawnInner",
            [i = 10]() mutable -> Poll<int> {
              GetContext<Activity>()->ForceImmediateRepoll();
              --i;
              if (i == 0) return 42;
              return Pending{};
            },
            [&n2](int x) {
              EXPECT_EQ(x, 42);
              n2.Notify();
            });
        return 1234;
      },
      [&n1](int x) {
        EXPECT_EQ(x, 1234);
        n1.Notify();
      });
  n1.WaitForNotification();
  n2.WaitForNotification();
}

TEST_F(PartyTest, CanWakeupWithOwningWaker) {
  auto party = MakeParty();
  Notification n[10];
  Notification complete;
  Waker waker;
  party->Spawn(
      "TestSpawn",
      [i = 0, &waker, &n]() mutable -> Poll<int> {
        waker = GetContext<Activity>()->MakeOwningWaker();
        n[i].Notify();
        i++;
        if (i == 10) return 42;
        return Pending{};
      },
      [&complete](int x) {
        EXPECT_EQ(x, 42);
        complete.Notify();
      });
  for (int i = 0; i < 10; i++) {
    n[i].WaitForNotification();
    waker.Wakeup();
  }
  complete.WaitForNotification();
}

TEST_F(PartyTest, CanWakeupWithNonOwningWaker) {
  auto party = MakeParty();
  Notification n[10];
  Notification complete;
  Waker waker;
  party->Spawn(
      "TestSpawn",
      [i = 10, &waker, &n]() mutable -> Poll<int> {
        waker = GetContext<Activity>()->MakeNonOwningWaker();
        --i;
        n[9 - i].Notify();
        if (i == 0) return 42;
        return Pending{};
      },
      [&complete](int x) {
        EXPECT_EQ(x, 42);
        complete.Notify();
      });
  for (int i = 0; i < 9; i++) {
    n[i].WaitForNotification();
    EXPECT_FALSE(n[i + 1].HasBeenNotified());
    waker.Wakeup();
  }
  complete.WaitForNotification();
}

TEST_F(PartyTest, CanWakeupWithNonOwningWakerAfterOrphaning) {
  auto party = MakeParty();
  Notification set_waker;
  Waker waker;
  party->Spawn(
      "TestSpawn",
      [&waker, &set_waker]() mutable -> Poll<int> {
        EXPECT_FALSE(set_waker.HasBeenNotified());
        waker = GetContext<Activity>()->MakeNonOwningWaker();
        set_waker.Notify();
        return Pending{};
      },
      [](int) { Crash("unreachable"); });
  set_waker.WaitForNotification();
  party.reset();
  EXPECT_FALSE(waker.is_unwakeable());
  waker.Wakeup();
  EXPECT_TRUE(waker.is_unwakeable());
}

TEST_F(PartyTest, CanDropNonOwningWakeAfterOrphaning) {
  auto party = MakeParty();
  Notification set_waker;
  std::unique_ptr<Waker> waker;
  party->Spawn(
      "TestSpawn",
      [&waker, &set_waker]() mutable -> Poll<int> {
        EXPECT_FALSE(set_waker.HasBeenNotified());
        waker = std::make_unique<Waker>(
            GetContext<Activity>()->MakeNonOwningWaker());
        set_waker.Notify();
        return Pending{};
      },
      [](int) { Crash("unreachable"); });
  set_waker.WaitForNotification();
  party.reset();
  EXPECT_NE(waker, nullptr);
  waker.reset();
}

TEST_F(PartyTest, CanWakeupNonOwningOrphanedWakerWithNoEffect) {
  auto party = MakeParty();
  Notification set_waker;
  Waker waker;
  party->Spawn(
      "TestSpawn",
      [&waker, &set_waker]() mutable -> Poll<int> {
        EXPECT_FALSE(set_waker.HasBeenNotified());
        waker = GetContext<Activity>()->MakeNonOwningWaker();
        set_waker.Notify();
        return Pending{};
      },
      [](int) { Crash("unreachable"); });
  set_waker.WaitForNotification();
  EXPECT_FALSE(waker.is_unwakeable());
  party.reset();
  waker.Wakeup();
  EXPECT_TRUE(waker.is_unwakeable());
}

TEST_F(PartyTest, CanBulkSpawn) {
  auto party = MakeParty();
  Notification n1;
  Notification n2;
  {
    Party::WakeupHold hold(party.get());
    party->Spawn("spawn1", []() {}, [&n1](Empty) { n1.Notify(); });
    party->Spawn("spawn2", []() {}, [&n2](Empty) { n2.Notify(); });
    for (int i = 0; i < 5000; i++) {
      EXPECT_FALSE(n1.HasBeenNotified());
      EXPECT_FALSE(n2.HasBeenNotified());
    }
  }
  n1.WaitForNotification();
  n2.WaitForNotification();
}

TEST_F(PartyTest, CanNestWakeupHold) {
  auto party = MakeParty();
  Notification n1;
  Notification n2;
  {
    Party::WakeupHold hold1(party.get());
    Party::WakeupHold hold2(party.get());
    party->Spawn("spawn1", []() {}, [&n1](Empty) { n1.Notify(); });
    party->Spawn("spawn2", []() {}, [&n2](Empty) { n2.Notify(); });
    for (int i = 0; i < 5000; i++) {
      EXPECT_FALSE(n1.HasBeenNotified());
      EXPECT_FALSE(n2.HasBeenNotified());
    }
  }
  n1.WaitForNotification();
  n2.WaitForNotification();
}

TEST_F(PartyTest, ThreadStressTest) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 100; i++) {
        ExecCtx ctx;  // needed for Sleep
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(Sleep(Timestamp::Now() + Duration::Milliseconds(10)),
                         []() -> Poll<int> { return 42; }),
                     [&promise_complete](int i) {
                       EXPECT_EQ(i, 42);
                       promise_complete.Notify();
                     });
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

class PromiseNotification {
 public:
  explicit PromiseNotification(bool owning_waker)
      : owning_waker_(owning_waker) {}

  auto Wait() {
    return [this]() -> Poll<int> {
      MutexLock lock(&mu_);
      if (done_) return 42;
      if (!polled_) {
        if (owning_waker_) {
          waker_ = GetContext<Activity>()->MakeOwningWaker();
        } else {
          waker_ = GetContext<Activity>()->MakeNonOwningWaker();
        }
        polled_ = true;
      }
      return Pending{};
    };
  }

  void Notify() {
    Waker waker;
    {
      MutexLock lock(&mu_);
      done_ = true;
      waker = std::move(waker_);
    }
    waker.Wakeup();
  }

  void NotifyUnderLock() {
    MutexLock lock(&mu_);
    done_ = true;
    waker_.WakeupAsync();
  }

 private:
  Mutex mu_;
  const bool owning_waker_;
  bool done_ ABSL_GUARDED_BY(mu_) = false;
  bool polled_ ABSL_GUARDED_BY(mu_) = false;
  Waker waker_ ABSL_GUARDED_BY(mu_);
};

TEST_F(PartyTest, ThreadStressTestWithOwningWaker) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 100; i++) {
        ExecCtx ctx;  // needed for Sleep
        PromiseNotification promise_start(true);
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(promise_start.Wait(),
                         Sleep(Timestamp::Now() + Duration::Milliseconds(10)),
                         []() -> Poll<int> { return 42; }),
                     [&promise_complete](int i) {
                       EXPECT_EQ(i, 42);
                       promise_complete.Notify();
                     });
        promise_start.Notify();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithOwningWakerHoldingLock) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 100; i++) {
        ExecCtx ctx;  // needed for Sleep
        PromiseNotification promise_start(true);
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(promise_start.Wait(),
                         Sleep(Timestamp::Now() + Duration::Milliseconds(10)),
                         []() -> Poll<int> { return 42; }),
                     [&promise_complete](int i) {
                       EXPECT_EQ(i, 42);
                       promise_complete.Notify();
                     });
        promise_start.NotifyUnderLock();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithNonOwningWaker) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 100; i++) {
        ExecCtx ctx;  // needed for Sleep
        PromiseNotification promise_start(false);
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(promise_start.Wait(),
                         Sleep(Timestamp::Now() + Duration::Milliseconds(10)),
                         []() -> Poll<int> { return 42; }),
                     [&promise_complete](int i) {
                       EXPECT_EQ(i, 42);
                       promise_complete.Notify();
                     });
        promise_start.Notify();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithOwningWakerNoSleep) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 10000; i++) {
        PromiseNotification promise_start(true);
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(promise_start.Wait(), []() -> Poll<int> { return 42; }),
            [&promise_complete](int i) {
              EXPECT_EQ(i, 42);
              promise_complete.Notify();
            });
        promise_start.Notify();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithNonOwningWakerNoSleep) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 10000; i++) {
        PromiseNotification promise_start(false);
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(promise_start.Wait(), []() -> Poll<int> { return 42; }),
            [&promise_complete](int i) {
              EXPECT_EQ(i, 42);
              promise_complete.Notify();
            });
        promise_start.Notify();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithInnerSpawn) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < 100; i++) {
        ExecCtx ctx;  // needed for Sleep
        PromiseNotification inner_start(true);
        PromiseNotification inner_complete(false);
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(
                [party, &inner_start, &inner_complete]() -> Poll<int> {
                  party->Spawn("TestSpawnInner",
                               Seq(inner_start.Wait(), []() { return 0; }),
                               [&inner_complete](int i) {
                                 EXPECT_EQ(i, 0);
                                 inner_complete.Notify();
                               });
                  return 0;
                },
                Sleep(Timestamp::Now() + Duration::Milliseconds(10)),
                [&inner_start]() {
                  inner_start.Notify();
                  return 0;
                },
                inner_complete.Wait(), []() -> Poll<int> { return 42; }),
            [&promise_complete](int i) {
              EXPECT_EQ(i, 42);
              promise_complete.Notify();
            });
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, NestedWakeup) {
  auto party1 = MakeParty();
  auto party2 = MakeParty();
  auto party3 = MakeParty();
  int whats_going_on = 0;
  Notification done1;
  Notification started2;
  Notification done2;
  Notification started3;
  Notification notify_done;
  party1->Spawn(
      "p1",
      [&]() {
        EXPECT_EQ(whats_going_on, 0);
        whats_going_on = 1;
        party2->Spawn(
            "p2",
            [&]() {
              done1.WaitForNotification();
              started2.Notify();
              started3.WaitForNotification();
              EXPECT_EQ(whats_going_on, 3);
              whats_going_on = 4;
            },
            [&](Empty) {
              EXPECT_EQ(whats_going_on, 4);
              whats_going_on = 5;
              done2.Notify();
            });
        party3->Spawn(
            "p3",
            [&]() {
              started2.WaitForNotification();
              started3.Notify();
              done2.WaitForNotification();
              EXPECT_EQ(whats_going_on, 5);
              whats_going_on = 6;
            },
            [&](Empty) {
              EXPECT_EQ(whats_going_on, 6);
              whats_going_on = 7;
              notify_done.Notify();
            });
        EXPECT_EQ(whats_going_on, 1);
        whats_going_on = 2;
      },
      [&](Empty) {
        EXPECT_EQ(whats_going_on, 2);
        whats_going_on = 3;
        done1.Notify();
      });
  notify_done.WaitForNotification();
}

// Testing Promise Parties with MPSC Queues

struct Payload {
  std::unique_ptr<int> x;
  bool operator==(const Payload& other) const {
    return (x == nullptr && other.x == nullptr) ||
           (x != nullptr && other.x != nullptr && *x == *other.x);
  }
  bool operator!=(const Payload& other) const { return !(*this == other); }
  explicit Payload(std::unique_ptr<int> x) : x(std::move(x)) {}
  Payload(const Payload& other)
      : x(other.x ? std::make_unique<int>(*other.x) : nullptr) {}

  friend std::ostream& operator<<(std::ostream& os, const Payload& payload) {
    if (payload.x == nullptr) return os << "Payload{nullptr}";
    return os << "Payload{" << *payload.x << "}";
  }
};

Payload MakePayload(int value) { return Payload{std::make_unique<int>(value)}; }

auto MakeSenderPromise(MpscSender<Payload>& sender, Notification& sent) {
  return [&sender, &sent]() {
    auto send_promise = sender.Send(MakePayload(42));
    Poll<bool> send_result = send_promise();
    EXPECT_TRUE(send_result.ready());
    EXPECT_TRUE(send_result.value());
    sent.Notify();
  };
}

auto MakeReceiverPromise(MpscReceiver<Payload>& receiver, Notification& sent) {
  return [&receiver, &sent]() {
    sent.WaitForNotification();
    auto receive_promise = receiver.Next();
    Poll<ValueOrFailure<Payload>> receive_result = receive_promise();
    EXPECT_TRUE(receive_result.ready());
    EXPECT_EQ(receive_result.value(), MakePayload(42));
  };
}

auto OnCompleteNotify(Notification& notification) {
  return [&notification](Empty) { notification.Notify(); };
}

auto OnCompleteNoop() {
  return [](Empty) {};
}

TEST_F(PartyTest, MpscTest) {
  // Number of Receivers = 1  // Will be 1 always for MPSC
  // Number of Senders   = 1
  // Number of Payloads  = 1
  // Number of Parties   = 1
  // Number of Threads   = 1

  // Basic MPSC & Party test.
  MpscReceiver<Payload> receiver(1);
  MpscSender<Payload> sender = receiver.MakeSender();
  auto party = MakeParty();
  Notification sent;
  Notification received;
  auto sender_promise = MakeSenderPromise(sender, sent);
  auto receiver_promise = MakeReceiverPromise(receiver, sent);
  party->Spawn("sender", sender_promise, OnCompleteNotify(received));
  party->Spawn("receiver", receiver_promise, OnCompleteNoop());
  received.WaitForNotification();
  // TODO(tjagtap): Is this how we want to use the MPSC for HTTP2 Transports?
  // TODO(tjagtap): Is there some notification we can wait on when something
  // is ready to be read?
  // TODO(tjagtap): This crashes!! Is that expected?
  // auto nothing = receiver.Next()();
}

TEST_F(PartyTest, MpscStressTestOneParty) {
  // Number of Receivers = 1  // Will be 1 always for MPSC
  // Number of Senders   = 10
  // Number of Payloads  = 10 Senders * 100 spawns = 1000
  // Number of Parties   = 1
  // Number of Threads   = 11

  // Stress testing MPSC & Party.
}

TEST_F(PartyTest, MpscStressTestManyParties) {
  // Number of Receivers = 1  // Will be 1 always for MPSC
  // Number of Senders   = 10
  // Number of Payloads  = 10 Senders * 100 spawns = 1000
  // Number of Parties   = 10
  // Number of Threads   = 11
  // Stress testing MPSC & Party.
  // This is the same as the above test, but with multiple parties.
  // Using 10 parties, each with 10 threads will ensure that we have 10 threads
  // concurrently trying to send on the same MPSC.

  // TODO(tjagtap): What do I need to do to make sure that event engine actually
  // gives me 10 threads all for this test?
}

}  // namespace grpc_core

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
