#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/Scene.hpp>
#include <systems/RenderSystem.hpp>

namespace ren {

class Window
{
public:
    Window(
        const std::string& name, 
        const int width, 
        const int height
    );
    virtual ~Window();

    bool isOpen();
    void render(Scene& scene); 

    int getWidth() const;
    int getHeight() const;
    const std::string& getName() const;
    GLFWwindow* getGLFWwindow() const;

    void setWidth(int width);
    void setHeight(int height);
    void setName(const std::string& name);

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);   

private:
    int width;
    int height;
    std::string name;
    GLFWwindow* _window;
};

}