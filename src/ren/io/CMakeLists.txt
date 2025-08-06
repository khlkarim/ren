file(GLOB_RECURSE IO_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/ren/io/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/ren/io/*.hpp
)

add_library(io STATIC ${IO_SOURCES})

target_include_directories(io PUBLIC ${CMAKE_SOURCE_DIR}/include/ren)
target_link_libraries(io PUBLIC core)