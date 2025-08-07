file(GLOB_RECURSE PHYSICS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/ren/physics/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/ren/physics/*.hpp
)

add_library(physics STATIC ${PHYSICS_SOURCES})

target_include_directories(physics PUBLIC ${CMAKE_SOURCE_DIR}/include/ren)
target_link_libraries(physics PUBLIC ecs)