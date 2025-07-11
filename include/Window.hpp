#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "Scene.hpp"

class Window
{
public:
    Window(const std::string& name, const int width, const int height);
    virtual ~Window();

    void render(Scene& scene);
    bool isOpen();

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);    
private:
    int width;
    int height;
    std::string name;
    GLFWwindow* _window;
};

#endif // WINDOW_HPP