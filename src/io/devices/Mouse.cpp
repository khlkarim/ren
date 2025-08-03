#include <core/Window.hpp>
#include <io/events/mouse/Moved.hpp>
#include <io/events/mouse/Clicked.hpp>
#include <io/events/mouse/Entered.hpp>
#include <io/events/mouse/Scrolled.hpp>
#include <io/devices/Mouse.hpp>
using ren::Window;
using ren::io::events::Event;
using ren::io::devices::Mouse;
using namespace ren::io::events::mouse;

std::unique_ptr<Mouse> Mouse::instance = nullptr;

Mouse::Mouse(GLFWwindow* window)
    : window(window), xpos(0), ypos(0), prev_xpos(0), prev_ypos(0), first_move(true)
{}

Mouse::Mouse()
    : window(nullptr), xpos(0), ypos(0), prev_xpos(0), prev_ypos(0), first_move(true)
{}

Mouse& Mouse::getInstance()
{
    if (!instance) {
        instance = std::move(std::unique_ptr<Mouse>(new Mouse()));
    }
    return *instance;
}

Mouse& Mouse::listen(const Window& window)
{   
    if (!instance) {
        instance = std::move(std::unique_ptr<Mouse>(new Mouse(window.getGLFWwindow())));
    }
    set_callbacks(window.getGLFWwindow());

    return *instance;
}

GLFWwindow* Mouse::getWindow() const
{
    return this->window;
}

void Mouse::set_callbacks(GLFWwindow* window)
{
    glfwSetMouseButtonCallback(window, clicked_callback);
    glfwSetCursorEnterCallback(window, entered_callback);
    glfwSetCursorPosCallback(window, moved_callback);
    glfwSetScrollCallback(window, scrolled_callback);
}

void Mouse::clicked_callback(GLFWwindow* window, int button, int action, int mods)
{
    Clicked event(window, button, action, mods);

    if(action == GLFW_PRESS)
    {
        instance->keysPressed[button] = event;
    }
    else if(action == GLFW_RELEASE)
    {
        instance->keysPressed.erase(button);
    }

    instance->emit(Clicked(window, button, action, mods));
}
void Mouse::entered_callback(GLFWwindow* window, int entered)
{
    instance->emit(Entered(window, entered));
}
void Mouse::moved_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (instance->first_move) {
        instance->prev_xpos = xpos;
        instance->prev_ypos = ypos;
        instance->first_move = false;
    } else {
        instance->prev_xpos = instance->xpos;
        instance->prev_ypos = instance->ypos;
    }

    instance->xpos = xpos;
    instance->ypos = ypos;

    instance->emit(Moved(window, xpos, ypos));
}
void Mouse::scrolled_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    instance->emit(Scrolled(window, xoffset, yoffset));
}

std::optional<Clicked> Mouse::isPressed(int key)
{
    if(this->keysPressed.find(key) != this->keysPressed.end())
    {  
        return this->keysPressed[key];
    }
    else
    {   
        return std::nullopt;
    }
}

double Mouse::getXPos() const
{
    return xpos;
}

double Mouse::getYPos() const
{
    return ypos;
}

double Mouse::getDeltaX() const
{
    return xpos - prev_xpos;
}

double Mouse::getDeltaY() const
{
    return ypos - prev_ypos;
}

void Mouse::consumeDelta()
{
    prev_xpos = xpos;
    prev_ypos = ypos;
}