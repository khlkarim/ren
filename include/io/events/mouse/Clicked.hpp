#pragma once

#include <io/Event.hpp>

namespace ren::io::events::mouse
{

class Clicked: public Event
{
public:
    Clicked(
        GLFWwindow* window,
        int button,
        int action,
        int mods
    ) : Event(window), button(button), action(action), mods(mods) {}

    int button;
    int action;
    int mods;
};

}