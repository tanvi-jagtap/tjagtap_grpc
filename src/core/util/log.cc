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

#include <grpc/support/port_platform.h>

#include "absl/log/log.h"

#include <stdio.h>
#include <string.h>

#include "absl/log/globals.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"

#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/log.h>

#include "src/core/lib/config/config_vars.h"
#include "src/core/lib/gprpp/crash.h"
#include "src/core/util/string.h"

void gpr_unreachable_code(const char* reason, const char* file, int line) {
  grpc_core::Crash(absl::StrCat("UNREACHABLE CODE: ", reason),
                   grpc_core::SourceLocation(file, line));
}

int grpc_absl_vlog2_enabled() { return ABSL_VLOG_IS_ON(2); }

GPRAPI void grpc_absl_log_error(const char* file, int line,
                                const char* message_str) {
  LOG(ERROR).AtLocation(file, line) << message_str;
}

GPRAPI void grpc_absl_log_info(const char* file, int line,
                               const char* message_str) {
  LOG(INFO).AtLocation(file, line) << message_str;
}

GPRAPI void grpc_absl_log_info_int(const char* file, int line,
                                   const char* message_str, intptr_t num) {
  LOG(INFO).AtLocation(file, line) << message_str << num;
}

GPRAPI void grpc_absl_vlog(const char* file, int line,
                           const char* message_str) {
  VLOG(2).AtLocation(file, line) << message_str;
}

GPRAPI void grpc_absl_vlog_int(const char* file, int line,
                               const char* message_str, intptr_t num) {
  VLOG(2).AtLocation(file, line) << message_str << num;
}

void gpr_log_verbosity_init(void) {
// This is enabled in Github only.
// This ifndef is converted to ifdef internally by copybara.
// Internally grpc verbosity is managed using absl settings.
// So internally we avoid setting it like this.
#ifndef GRPC_VERBOSITY_MACRO
  // SetMinLogLevel sets the value for the entire binary, not just gRPC.
  // This setting will change things for other libraries/code that is unrelated
  // to grpc.
  absl::string_view verbosity = grpc_core::ConfigVars::Get().Verbosity();
  if (absl::EqualsIgnoreCase(verbosity, "INFO")) {
    LOG_FIRST_N(WARNING, 1)
        << "Log level INFO is not suitable for production. Prefer WARNING or "
           "ERROR. However if you see this message in a debug environmenmt or "
           "test environmenmt it is safe to ignore this message.";
    absl::SetVLogLevel("*grpc*/*", -1);
    absl::SetMinLogLevel(absl::LogSeverityAtLeast::kInfo);
  } else if (absl::EqualsIgnoreCase(verbosity, "DEBUG")) {
    LOG_FIRST_N(WARNING, 1)
        << "Log level DEBUG is not suitable for production. Prefer WARNING or "
           "ERROR. However if you see this message in a debug environmenmt or "
           "test environmenmt it is safe to ignore this message.";
    absl::SetVLogLevel("*grpc*/*", 2);
    absl::SetMinLogLevel(absl::LogSeverityAtLeast::kInfo);
  } else if (absl::EqualsIgnoreCase(verbosity, "ERROR")) {
    absl::SetVLogLevel("*grpc*/*", -1);
    absl::SetMinLogLevel(absl::LogSeverityAtLeast::kError);
  } else if (absl::EqualsIgnoreCase(verbosity, "NONE")) {
    absl::SetVLogLevel("*grpc*/*", -1);
    absl::SetMinLogLevel(absl::LogSeverityAtLeast::kInfinity);
  } else if (verbosity.empty()) {
    // Do not alter absl settings if GRPC_VERBOSITY flag is not set.
  } else {
    LOG(ERROR) << "Unknown log verbosity: " << verbosity;
  }
#endif  // GRPC_VERBOSITY_MACRO
}
