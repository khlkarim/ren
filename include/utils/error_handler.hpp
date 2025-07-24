#pragma once

#include <cstdlib>
#include <spdlog/spdlog.h>

[[noreturn]] void fatal(const std::string& message);