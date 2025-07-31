#pragma once

#include <string>
#include <vector>
#include <functional>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <core/Window.hpp>
#include <io/Event.hpp>
#include <io/events/keyboard/KeyInput.hpp>
#include <io/events/mouse/Clicked.hpp>
#include <io/events/mouse/Entered.hpp>
#include <io/events/mouse/Moved.hpp>
#include <io/events/mouse/Scrolled.hpp>

namespace ren::io
{

class InputSystem
{
public:
    static InputSystem& getInstance();
    static InputSystem& listen(const Window& window);

    template<typename T>
    void on(const std::function<void(const T&)>& callback);

    template<typename T>
    void if_active(const std::function<void(const T&)>& callback);

private:
    InputSystem() = default;
    InputSystem(GLFWwindow* window);
    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;

    template<typename T>
    void emit(const T& event);

    static void set_callbacks(GLFWwindow* window);
    static void set_mouse_callbacks(GLFWwindow* window);
    static void set_keyboard_callbacks(GLFWwindow* window);

    // Keyboard
    static void key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Mouse
    static void clicked_callback(GLFWwindow* window, int button, int action, int mods);
    static void entered_callback(GLFWwindow* window, int entered);
    static void moved_callback(GLFWwindow* window, double xpos, double ypos);
    static void scrolled_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    static std::unique_ptr<InputSystem> instance;
    GLFWwindow* window;
    std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> callbacks;
};

}

template<typename T>
void ren::io::InputSystem::emit(const T& event) {
    auto it = callbacks.find(typeid(T));
    if (it != callbacks.end()) {
        for (auto& cb : it->second) {
            cb(event);
        }
    }
}

template<typename T>
void ren::io::InputSystem::on(const std::function<void(const T&)>& callback) {
    callbacks[typeid(T)].emplace_back([callback](const Event& event) {
        callback(dynamic_cast<const T&>(event));
    });
}

template<typename T>
void ren::io::InputSystem::if_active(const std::function<void(const T&)>& callback)
{
    std::optional<T> event = T::poll(this->window);

    if(event)
    {
        callback(*event);
    }
}