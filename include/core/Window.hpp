#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/Scene.hpp>

namespace ren {

class Window
{
public:
    Window(
        const std::string& name, 
        const unsigned int width, 
        const unsigned int height,
        const unsigned int fps = 0
    );
    virtual ~Window();

    bool isOpen();
    void render(Scene& scene); 

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getTargetFPS() const;
    const std::string& getName() const;
    GLFWwindow* getGLFWwindow() const;

    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setName(const std::string& name);
    void setTargetFPS(unsigned int fps);

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);   

private:
    std::string name;
    unsigned int width;
    unsigned int height;
    unsigned int fps;

    GLFWwindow* _window;
};

}