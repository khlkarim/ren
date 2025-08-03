#include <spdlog/spdlog.h>
#include <core/Window.hpp>
#include <core/Scene.hpp>

using ren::Window;

Window::Window(const std::string& name, const unsigned int width, const unsigned int height, const unsigned int fps) 
{
    this->name = name;
    this->width = width;
    this->height = height;
    this->fps = fps;

    spdlog::info("Window Constructor");

    if(!glfwInit()) {
        spdlog::critical("Failed to initialize GLFW");
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    spdlog::info("Initialized GLFW");
    
    this->_window = glfwCreateWindow(this->width, this->height, this->name.c_str(), NULL, NULL);
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
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
    spdlog::info("Initialized glad");
    spdlog::info("Set framebuffer size callback");

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(this->_window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);   
    spdlog::info("Set GL viewport");

    glfwSwapInterval(1);
}

Window::~Window() 
{
    spdlog::info("Window Destructor");

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

void Window::render(Scene& scene)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

    scene.render();

    glfwSwapBuffers(this->_window);
}

unsigned int Window::getWidth() const {
    return this->width;
}

unsigned int Window::getHeight() const {
    return this->height;
}

unsigned int Window::getTargetFPS() const {
    return this->fps;
}

const std::string& Window::getName() const {
    return this->name;
}

GLFWwindow* Window::getGLFWwindow() const {
    return this->_window;
}

void Window::setWidth(unsigned int width) {
    this->width = width;
    glfwSetWindowSize(this->_window, this->width, this->height);
}

void Window::setHeight(unsigned int height) {
    this->height = height;
    glfwSetWindowSize(this->_window, this->width, this->height);
}

void Window::setName(const std::string& name) {
    this->name = name;
    glfwSetWindowTitle(this->_window, this->name.c_str());
}

void Window::setTargetFPS(unsigned int fps) 
{
    this->fps = fps;
}

void ren::framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{  
    glViewport(0, 0, width, height);
}