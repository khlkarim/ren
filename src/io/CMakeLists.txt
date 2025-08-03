file(GLOB_RECURSE IO_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/io/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/io/*.hpp
)

add_library(io STATIC ${IO_SOURCES})

target_include_directories(io PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(io PUBLIC core)