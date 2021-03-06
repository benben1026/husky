// Copyright 2016 Husky Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>

// FIXME(Legend): This include is only used for test now, which is not self-sufficient.
#include "glog/logging.h"

namespace husky {
namespace base {

enum class LOG_TYPE {
    LOG_INFO = 1,
    LOG_DEBUG = 1 << 1,
    LOG_ERROR = 1 << 2,
    LOG_WARNING = 1 << 3,
};

void log_msg(const std::string& msg, LOG_TYPE type = LOG_TYPE::LOG_INFO);
void log_msg_to_file(const std::string& msg, LOG_TYPE type, const std::string& file_name);

void log_info(const std::string& msg);
void log_debug(const std::string& msg);
void log_error(const std::string& msg);
void log_warning(const std::string& msg);

}  // namespace base
}  // namespace husky
