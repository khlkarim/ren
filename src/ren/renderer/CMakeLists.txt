file(GLOB_RECURSE RENDERER_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/ren/renderer/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/ren/renderer/*.hpp
)

add_library(renderer STATIC ${RENDERER_SOURCES})

target_include_directories(renderer PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(renderer PUBLIC core io)