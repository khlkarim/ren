file(GLOB TESTS ${CMAKE_SOURCE_DIR}/test/*/*.cpp)

foreach(TEST_SRC ${TESTS})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} PRIVATE core physics renderer assets imgui::imgui OpenGL::GL)
endforeach()