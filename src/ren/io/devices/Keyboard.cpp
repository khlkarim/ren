#include "imgui.h"
#include <spdlog/spdlog.h>
#include "core/Window.hpp"
#include "io/events/keyboard/KeyInput.hpp"
#include "io/devices/Keyboard.hpp"
using ren::core::Window;
using ren::io::events::Event;
using ren::io::devices::Keyboard;
using namespace ren::io::events::keyboard;

std::unique_ptr<Keyboard> Keyboard::instance = nullptr;

Keyboard::Keyboard(GLFWwindow* window)
{
    this->window = window;
}

Keyboard& Keyboard::getInstance()
{
    if (!instance) {
        instance = std::move(std::unique_ptr<Keyboard>(new Keyboard()));
    }
    return *instance;
}

Keyboard& Keyboard::listen(const Window& window)
{   
    if (!instance) {
        instance = std::move(std::unique_ptr<Keyboard>(new Keyboard(window.getGlfwWindow())));
    }
    set_callbacks(window.getGlfwWindow());

    return *instance;
}

GLFWwindow* Keyboard::getWindow() const
{
    return this->window;
}

void Keyboard::set_callbacks(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_input_callback);
}

void Keyboard::key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureKeyboard) return;

    KeyInput event(window, key, scancode, action, mods);

    if(action == GLFW_PRESS)
    {
        instance->keysPressed[key] = event;
    }
    else if(action == GLFW_RELEASE)
    {
        instance->keysPressed.erase(key);
    }

    instance->emit(event);
}

std::optional<KeyInput> Keyboard::isPressed(int key)
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