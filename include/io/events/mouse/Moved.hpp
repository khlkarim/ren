#pragma once

#include <io/Event.hpp>

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
};

}