#pragma once

#include <cstdlib>
#include <spdlog/spdlog.h>

#define FATAL(fmt, ...) \
    do {\
        spdlog::error(fmt + std::string(" ({}:{})"), __VA_ARGS__, __FILE__, __LINE__);\
        std::exit(EXIT_FAILURE);\
    } while(0)