#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <io/events/Event.hpp>
#include <io/events/keyboard/KeyInput.hpp>

namespace ren 
{
    class Window;
}

namespace ren::io::devices
{

class Keyboard
{
public:
    static Keyboard& getInstance();
    static Keyboard& listen(const Window& window);

    template<typename T>
    void on(const std::function<void(const T&)>& callback);

    template<typename T>
    std::optional<T> poll();

    GLFWwindow* getWindow() const;
    std::optional<events::keyboard::KeyInput> isPressed(int key);

private:
    Keyboard() = default;
    Keyboard(GLFWwindow* window);
    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;

    template<typename T>
    void emit(const T& event);

    static void set_callbacks(GLFWwindow* window);
    static void key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    static std::unique_ptr<Keyboard> instance;
    GLFWwindow* window;
    std::unordered_map<int, events::keyboard::KeyInput> keysPressed;
    std::unordered_map<std::type_index, std::vector<std::function<void(const events::Event&)>>> callbacks;
};

}

template<typename T>
void ren::io::devices::Keyboard::emit(const T& event) {
    auto it = callbacks.find(typeid(T));
    if (it != callbacks.end()) {
        for (auto& cb : it->second) {
            cb(event);
        }
    }
}

template<typename T>
void ren::io::devices::Keyboard::on(const std::function<void(const T&)>& callback) {
    callbacks[typeid(T)].emplace_back([callback](const events::Event& event) {
        callback(dynamic_cast<const T&>(event));
    });
}

template<typename T>
std::optional<T> ren::io::devices::Keyboard::poll()
{
    return T::poll(this->window);
}