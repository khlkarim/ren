#pragma once

#include <io/Event.hpp>

namespace ren::io::events::mouse
{

class Scrolled: public Event
{
public:
    Scrolled(
        GLFWwindow* window,
        double xoffset,
        double yoffset
    ) : Event(window), xoffset(xoffset), yoffset(yoffset) {}

    double xoffset;
    double yoffset;
};

}