file(GLOB_RECURSE SYSTEMS_SOURCES 
    ${CMAKE_SOURCE_DIR}/src/systems/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/systems/*.hpp
)

add_library(systems STATIC ${SYSTEMS_SOURCES})

target_include_directories(systems PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(systems PUBLIC io)