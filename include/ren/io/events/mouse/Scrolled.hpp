#pragma once

#include "io/events/Event.hpp"

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

    static std::optional<Scrolled> poll(GLFWwindow* window);
};

}