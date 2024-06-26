//
//
// Copyright 2015 gRPC authors.
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

#ifndef GRPC_TEST_CORE_TEST_UTIL_TRACER_UTIL_H
#define GRPC_TEST_CORE_TEST_UTIL_TRACER_UTIL_H

namespace grpc_core {
class TraceFlag;

namespace testing {
// enables the TraceFlag passed to it. Used for testing purposes.
void grpc_tracer_enable_flag(TraceFlag* flag);

}  // namespace testing
}  // namespace grpc_core

#endif  // GRPC_TEST_CORE_TEST_UTIL_TRACER_UTIL_H
