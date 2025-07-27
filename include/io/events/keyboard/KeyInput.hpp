#pragma once

#include <string>
#include <io/Event.hpp>

namespace ren::io::events::keyboard
{

struct KeyInput: public Event
{
public:
    KeyInput(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods
    ) : Event(window), key(key), scancode(scancode), action(action), mods(mods) {};

    int key;
    int scancode;
    int action;
    int mods;
};

} 