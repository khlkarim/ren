file(GLOB_RECURSE UTILS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/utils/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/utils/*.hpp
)

add_library(utils STATIC ${UTILS_SOURCES})

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(utils PUBLIC spdlog::spdlog)