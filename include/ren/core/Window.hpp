#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ren::core
{

class Scene;
class Window
{
public:
    Window(
        const std::string& name, 
        const unsigned int width, 
        const unsigned int height
    );
    virtual ~Window();

    bool isOpen();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    const std::string& getName() const;
    GLFWwindow* getGLFWwindow() const;

    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setName(const std::string& name);

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);   

private:
    std::string name;
    unsigned int width;
    unsigned int height;

    GLFWwindow* _window;
};

}