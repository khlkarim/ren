#pragma once

#include <GLFW/glfw3.h>

namespace ren::io
{

class Event
{
public:
    Event(GLFWwindow* window) : window(window) {}
    virtual ~Event() = default;
    GLFWwindow* window;
};

}