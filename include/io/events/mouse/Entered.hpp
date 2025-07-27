#pragma once

#include <io/Event.hpp>

namespace ren::io::events::mouse
{

class Entered: public Event
{
public:
    Entered(GLFWwindow* window, int entered) : Event(window), entered(entered) {}

    int entered;
};

}