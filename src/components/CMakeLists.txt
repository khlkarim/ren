file(GLOB_RECURSE COMPONENTS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/components/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/components/*.hpp
)

add_library(components STATIC ${COMPONENTS_SOURCES})

target_include_directories(components PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(components PUBLIC glad::glad glm::glm utils)