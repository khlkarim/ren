#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.hpp"

namespace ren {

class Window
{
public:
    Window(const std::string& name, const int width, const int height);
    virtual ~Window();

    bool isOpen();
    void render(Scene& scene);

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);    
private:
    int width;
    int height;
    std::string name;
    GLFWwindow* _window;
};

}