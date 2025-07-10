#include "Window.hpp"

Window::Window(const std::string& name, const int width, const int height) 
{
    if(!glfwInit()) {
        spdlog::critical("Failed to initialize GLFW");
        exit(-1);
    }
    spdlog::info("Initialized GLFW");
    
    this->_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if(!this->_window) {
        spdlog::critical("Failed to create window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(this->_window);
    spdlog::info("Created a window");

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::critical("Failed to initialize glad");
        glfwDestroyWindow(this->_window);
        glfwTerminate();
        exit(-1);
    }
    glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
    spdlog::info("Initialized glad");
    spdlog::info("Set framebuffer size callback");

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(this->_window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);   
    spdlog::info("Set GL viewport");
}

Window::~Window() 
{
    if (this->_window) {
        glfwDestroyWindow(this->_window);
        spdlog::info("Destroyed window");
    }
    glfwTerminate();
    spdlog::info("Terminated GLFW");
}

bool Window::isOpen() 
{
    return !glfwWindowShouldClose(this->_window);
}

void Window::setScene(Scene& scene) 
{
    this->scene = scene;
}

void Window::render() const
{
    // Poll events form the last frame
    glfwPollEvents();

    // Render the scene

    // Display frame
    glfwSwapBuffers(this->_window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{  
    glViewport(0, 0, width, height);
}