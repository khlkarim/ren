#pragma once

#include <GLFW/glfw3.h>

namespace ren::utils::imgui
{
    void init(GLFWwindow* window);
    void startFrame();
    void endFrame();
    void terminate();

    namespace windows
    {
        void hello_world(GLFWwindow* window);
        void performance_monitor(float dt);
    }
}