file(GLOB_RECURSE ASSETS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/ren/assets/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/ren/assets/*.hpp
)

add_library(assets STATIC ${ASSETS_SOURCES})

target_include_directories(assets PUBLIC ${CMAKE_SOURCE_DIR}/include/ren)
target_link_libraries(assets PUBLIC ecs assimp::assimp)