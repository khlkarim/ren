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

    bool isOpen() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    const std::string& getName() const;
    GLFWwindow* getGlfwWindow() const;

    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setName(const std::string& name);

private:
    void initGLFW();
    void createWindow();
    void initGLAD();
    void setupViewport();

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);   

private:
    std::string m_name;
    unsigned int m_width;
    unsigned int m_height;

    GLFWwindow* m_window;
};

}