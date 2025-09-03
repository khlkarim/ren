#include <spdlog/spdlog.h>
#include "core/Scene.hpp"
#include "core/Window.hpp"

namespace ren::core {

Window::Window(const std::string& name, unsigned int width, unsigned int height) 
    : m_name(name)
    , m_width(width)
    , m_height(height)
    , m_window(nullptr)
{
    initGLFW();
    createWindow();
    initGLAD();
    setupViewport();
}

Window::~Window() 
{
    if (m_window) {
        glfwDestroyWindow(m_window);
        spdlog::info("Destroyed window");
    }
    glfwTerminate();
    spdlog::info("Terminated GLFW");
}

bool Window::isOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

unsigned int Window::getWidth() const 
{
    return m_width;
}

unsigned int Window::getHeight() const 
{
    return m_height;
}

const std::string& Window::getName() const 
{
    return m_name;
}

GLFWwindow* Window::getGlfwWindow() const 
{
    return m_window;
}

void Window::setWidth(unsigned int width) 
{
    m_width = width;
    glfwSetWindowSize(m_window, m_width, m_height);
}

void Window::setHeight(unsigned int height) 
{
    m_height = height;
    glfwSetWindowSize(m_window, m_width, m_height);
}

void Window::setName(const std::string& name) 
{
    m_name = name;
    glfwSetWindowTitle(m_window, m_name.c_str());
}

void Window::initGLFW()
{
    if (!glfwInit()) {
        spdlog::critical("Failed to initialize GLFW");
        exit(-1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    spdlog::info("Initialized GLFW");
}

void Window::createWindow()
{
    m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
    if (!m_window) {
        spdlog::critical("Failed to create window");
        glfwTerminate();
        exit(-1);
    }
    
    glfwMakeContextCurrent(m_window);
    spdlog::info("Created a window");
}

void Window::initGLAD()
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        spdlog::critical("Failed to initialize GLAD");
        glfwDestroyWindow(m_window);
        glfwTerminate();
        exit(-1);
    }
    
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    spdlog::info("Initialized GLAD");
    spdlog::info("Set framebuffer size callback");
}

void Window::setupViewport()
{
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
    glfwSwapInterval(1);

    spdlog::info("Set GL viewport");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {  
    glViewport(0, 0, width, height);
}

}
