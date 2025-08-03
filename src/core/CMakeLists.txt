file(GLOB_RECURSE CORE_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/core/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/core/*.hpp
)

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(core PUBLIC components glfw)