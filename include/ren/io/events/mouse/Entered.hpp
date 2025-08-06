#pragma once

#include "io/events/Event.hpp"

namespace ren::io::events::mouse
{

class Entered: public Event
{
public:
    Entered(GLFWwindow* window, int entered) : Event(window), entered(entered) {}

    int entered;

    static std::optional<Entered> poll(GLFWwindow* window);
};

}