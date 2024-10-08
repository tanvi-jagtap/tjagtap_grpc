//
//
// Copyright 2021 gRPC authors.
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

#include "src/cpp/server/csds/csds.h"

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/slice.h>

#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace grpc {
namespace xds {
namespace experimental {

using envoy::service::status::v3::ClientStatusRequest;
using envoy::service::status::v3::ClientStatusResponse;

namespace {

absl::StatusOr<ClientStatusResponse> DumpClientStatusResponse() {
  ClientStatusResponse response;
  grpc_slice serialized_client_config = grpc_dump_xds_configs();
  std::string bytes = StringFromCopiedSlice(serialized_client_config);
  grpc_slice_unref(serialized_client_config);
  if (!response.ParseFromString(bytes)) {
    return absl::InternalError("Failed to parse ClientStatusResponse.");
  }
  return response;
}

}  // namespace

Status ClientStatusDiscoveryService::StreamClientStatus(
    ServerContext* /*context*/,
    ServerReaderWriter<ClientStatusResponse, ClientStatusRequest>* stream) {
  ClientStatusRequest request;
  while (stream->Read(&request)) {
    absl::StatusOr<ClientStatusResponse> response = DumpClientStatusResponse();
    if (!response.ok()) {
      if (response.status().code() == absl::StatusCode::kUnavailable) {
        // If the xDS client is not initialized, return empty response
        stream->Write(ClientStatusResponse());
        continue;
      }
      return Status(static_cast<StatusCode>(response.status().raw_code()),
                    response.status().ToString());
    }
    stream->Write(*response);
  }
  return Status::OK;
}

Status ClientStatusDiscoveryService::FetchClientStatus(
    ServerContext* /*context*/, const ClientStatusRequest* /*request*/,
    ClientStatusResponse* response) {
  absl::StatusOr<ClientStatusResponse> s = DumpClientStatusResponse();
  if (!s.ok()) {
    if (s.status().code() == absl::StatusCode::kUnavailable) {
      // If the xDS client is not initialized, return empty response
      return Status::OK;
    }
    return Status(static_cast<StatusCode>(s.status().raw_code()),
                  s.status().ToString());
  }
  *response = std::move(*s);
  return Status::OK;
}

}  // namespace experimental
}  // namespace xds
}  // namespace grpc
