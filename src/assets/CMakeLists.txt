file(GLOB_RECURSE ASSETS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/assets/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/assets/*.hpp
)

add_library(assets STATIC ${ASSETS_SOURCES})

target_include_directories(assets PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(assets PUBLIC core assimp::assimp)