file(GLOB_RECURSE ECS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/ren/ecs/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/ren/ecs/*.hpp
)

add_library(ecs STATIC ${ECS_SOURCES})

target_include_directories(ecs PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ecs PUBLIC glad::glad utils)