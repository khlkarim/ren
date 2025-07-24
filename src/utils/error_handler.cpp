#include <utils/error_handler.hpp>

[[noreturn]] void fatal(const std::string& message)
{
    spdlog::error(message);
    std::exit(EXIT_FAILURE);
}