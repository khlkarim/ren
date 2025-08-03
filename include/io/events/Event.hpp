#pragma once

#include <optional>
#include <GLFW/glfw3.h>

namespace ren::io::events
{

class Event
{
public:
    Event() = default;
    Event(GLFWwindow* window) : window(window) {}
    virtual ~Event() = default;
    GLFWwindow* window;
};

}