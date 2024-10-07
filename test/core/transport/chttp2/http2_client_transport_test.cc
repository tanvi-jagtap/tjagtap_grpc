//
//
// Copyright 2024 gRPC authors.
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
//
//

#include "src/core/ext/transport/chttp2/transport/http2_client_transport.h"

#include <gtest/gtest.h>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc_core {
namespace http2 {

TEST(Http2ClientTransportTest, TestIfTestFails) {
  CHECK(false);  // WIP - Do Not Review yet.
}

}  // namespace http2
}  // namespace grpc_core
