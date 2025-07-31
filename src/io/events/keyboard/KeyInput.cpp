#include <io/events/keyboard/KeyInput.hpp>
using ren::io::events::keyboard::KeyInput;

std::optional<KeyInput> KeyInput::poll(GLFWwindow* window)
{
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
        int state = glfwGetKey(window, key);
        if (state == GLFW_PRESS || state == GLFW_REPEAT) {
            int scancode = glfwGetKeyScancode(key);
            int action = state;
            int mods = 0;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
                mods |= GLFW_MOD_SHIFT;
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
                mods |= GLFW_MOD_CONTROL;
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
                mods |= GLFW_MOD_ALT;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS)
                mods |= GLFW_MOD_SUPER;
            KeyInput input(window, key, scancode, action, mods);
            return input;
        }
    }
    return std::nullopt;
}