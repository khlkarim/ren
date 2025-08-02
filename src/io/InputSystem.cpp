#include <io/InputSystem.hpp>
using ren::Window;
using ren::io::Event;
using ren::io::InputSystem;
using namespace ren::io::events;

std::unique_ptr<InputSystem> InputSystem::instance = nullptr;

InputSystem::InputSystem(GLFWwindow* window)
{
    this->window = window;
}

InputSystem& InputSystem::getInstance()
{
    if (!instance) {
        instance = std::move(std::unique_ptr<InputSystem>(new InputSystem()));
    }
    return *instance;
}

InputSystem& InputSystem::listen(const Window& window)
{   
    if (!instance) {
        instance = std::move(std::unique_ptr<InputSystem>(new InputSystem(window.getGLFWwindow())));
    }
    set_callbacks(window.getGLFWwindow());

    return *instance;
}

GLFWwindow* InputSystem::getWindow() const
{
    return this->window;
}

void InputSystem::set_callbacks(GLFWwindow* window)
{
    set_mouse_callbacks(window);
    set_keyboard_callbacks(window);
}

void InputSystem::set_mouse_callbacks(GLFWwindow* window)
{
    glfwSetMouseButtonCallback(window, clicked_callback);
    glfwSetCursorEnterCallback(window, entered_callback);
    glfwSetCursorPosCallback(window, moved_callback);
    glfwSetScrollCallback(window, scrolled_callback);
}

void InputSystem::set_keyboard_callbacks(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_input_callback);
}

void InputSystem::key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    instance->emit(keyboard::KeyInput(window, key, scancode, action, mods));
}

void InputSystem::clicked_callback(GLFWwindow* window, int button, int action, int mods)
{
    instance->emit(mouse::Clicked(window, button, action, mods));
}
void InputSystem::entered_callback(GLFWwindow* window, int entered)
{
    instance->emit(mouse::Entered(window, entered));
}
void InputSystem::moved_callback(GLFWwindow* window, double xpos, double ypos)
{
    instance->emit(mouse::Moved(window, xpos, ypos));
}
void InputSystem::scrolled_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    instance->emit(mouse::Scrolled(window, xoffset, yoffset));
}