#pragma once

#include "io/events/Event.hpp"

namespace ren::io::events::mouse
{

class Moved: public Event
{   
public:
    Moved(
        GLFWwindow* window,
        double xpos,
        double ypos
    ) : Event(window), xpos(xpos), ypos(ypos) {}

    double xpos;
    double ypos;

    static std::optional<Moved> poll(GLFWwindow* window);
};

}