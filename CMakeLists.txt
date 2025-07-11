cmake_minimum_required(VERSION 3.10)
project(REN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS uuid)
find_package(spdlog CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE REN_SOURCES src/*.cpp include/*.hpp)
add_library(REN STATIC ${REN_SOURCES})
target_include_directories(REN
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/components
        ${CMAKE_CURRENT_SOURCE_DIR}/include/primitives
)
target_link_libraries(REN 
    PUBLIC 
        glfw
        glm::glm
        glad::glad 
        Boost::uuid 
        spdlog::spdlog 
        assimp::assimp 
)

add_executable(Scene_0 test/e2e/scene_0.cpp)
target_link_libraries(Scene_0 PRIVATE REN)