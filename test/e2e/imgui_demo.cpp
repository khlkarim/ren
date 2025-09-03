#include "ren/utils/imgui.hpp"
#include <spdlog/spdlog.h>
#include "ren/utils/Timer.hpp"
#include <GLFW/glfw3.h>
#include <stdio.h>

// Error callback for GLFW
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Demo", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    ren::utils::imgui::init(window);

    // Main loop
    ren::utils::Timer timer;
    timer.start();

    while (!glfwWindowShouldClose(window))
    {
        timer.update();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        ren::utils::imgui::startFrame();
        ren::utils::imgui::windows::hello_world(window);
        ren::utils::imgui::windows::performance_monitor(timer.getDeltaTime());
        ren::utils::imgui::endFrame();

        glfwSwapBuffers(window);
    }

    ren::utils::imgui::terminate();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
