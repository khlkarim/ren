#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <io/events/Event.hpp>
#include <io/events/mouse/Clicked.hpp>

namespace ren 
{
    class Window;
}

namespace ren::io::devices
{

class Mouse
{
public:
    static Mouse& getInstance();
    static Mouse& listen(const Window& window);

    template<typename T>
    void on(const std::function<void(const T&)>& callback);

    template<typename T>
    std::optional<T> poll();

    GLFWwindow* getWindow() const;
    std::optional<events::mouse::Clicked> isPressed(int key);
    
    double getXPos() const;
    double getYPos() const;
    double getDeltaX() const;
    double getDeltaY() const;
    void consumeDelta();

private:
    Mouse();
    Mouse(GLFWwindow* window);
    Mouse(const Mouse&) = delete;
    Mouse& operator=(const Mouse&) = delete;

    template<typename T>
    void emit(const T& event);

    static void set_callbacks(GLFWwindow* window);
    static void clicked_callback(GLFWwindow* window, int button, int action, int mods);
    static void entered_callback(GLFWwindow* window, int entered);
    static void moved_callback(GLFWwindow* window, double xpos, double ypos);
    static void scrolled_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    static std::unique_ptr<Mouse> instance;
    GLFWwindow* window;
    std::unordered_map<std::type_index, std::vector<std::function<void(const events::Event&)>>> callbacks;

    double xpos;
    double ypos;
    double prev_xpos;
    double prev_ypos;
    bool first_move;
    std::unordered_map<int, events::mouse::Clicked> keysPressed;
};

}

template<typename T>
void ren::io::devices::Mouse::emit(const T& event) {
    auto it = callbacks.find(typeid(T));
    if (it != callbacks.end()) {
        for (auto& cb : it->second) {
            cb(event);
        }
    }
}

template<typename T>
void ren::io::devices::Mouse::on(const std::function<void(const T&)>& callback) {
    callbacks[typeid(T)].emplace_back([callback](const events::Event& event) {
        callback(dynamic_cast<const T&>(event));
    });
}

template<typename T>
std::optional<T> ren::io::devices::Mouse::poll()
{
    return  T::poll(this->window);
}