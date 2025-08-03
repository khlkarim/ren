#pragma once

#include <string>
#include <io/events/Event.hpp>

namespace ren::io::events::keyboard
{

class KeyInput: public Event
{
public:
    KeyInput() = default;
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

    static std::optional<KeyInput> poll(GLFWwindow* window);
};

} 