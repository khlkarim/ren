#include <core/Window.hpp>
using ren::Window;

Window::Window(const std::string& name, const int width, const int height) 
{
    spdlog::info("Window Constructor");

    if(!glfwInit()) {
        spdlog::critical("Failed to initialize GLFW");
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    glEnable(GL_DEPTH_TEST);
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

void ren::framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{  
    glViewport(0, 0, width, height);
}