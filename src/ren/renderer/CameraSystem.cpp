#include <spdlog/spdlog.h>
#include "io/devices/Mouse.hpp"
#include "io/devices/Keyboard.hpp"
#include "io/events/mouse/Moved.hpp"
#include "io/events/mouse/Clicked.hpp"
#include "io/events/keyboard/KeyInput.hpp"
#include "renderer/Camera.hpp"
#include "renderer/CameraSystem.hpp"
using ren::renderer::Camera;
using ren::renderer::CameraSystem;

CameraSystem::CameraSystem()
{
    auto& mouse = ren::io::devices::Mouse::getInstance();
    auto& keyboard = ren::io::devices::Keyboard::getInstance();
    GLFWwindow* window = mouse.getWindow();

    this->cursorLocked = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    keyboard.on<ren::io::events::keyboard::KeyInput>([window, this](const auto& event)
        {
            if(event.key == GLFW_KEY_ESCAPE)
            {
                this->cursorLocked = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        });
    mouse.on<ren::io::events::mouse::Clicked>([window, this](const auto& event)
        {            
            if(event.action == GLFW_PRESS)
            {
                this->cursorLocked = true;  
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        });
}

void CameraSystem::update(const float dt, Camera& camera)
{   
    this->updatePosition(dt, camera);
    if(this->cursorLocked) this->updateDirection(dt, camera);
}

void CameraSystem::updateDirection(const float dt, Camera& camera)
{
    auto& mouse = ren::io::devices::Mouse::getInstance();
    auto& eventOpt =  mouse.poll<ren::io::events::mouse::Moved>();

    if(!eventOpt) return;
    auto& event = eventOpt.value();

    static bool firstMouse = true;
    static double lastX, lastY;

    if (firstMouse) {
        lastX = event.xpos;
        lastY = event.ypos;
        firstMouse = false;
    }

    float xoffset = static_cast<float>(event.xpos - lastX);
    float yoffset = static_cast<float>(lastY - event.ypos);

    lastX = event.xpos;
    lastY = event.ypos;

    const float sensitivity = 5.0f;
    xoffset *= sensitivity * dt;
    yoffset *= sensitivity * dt;

    camera.setYaw(camera.getYaw() + xoffset);
    camera.setPitch(camera.getPitch() + yoffset);
}

void CameraSystem::updatePosition(const float dt, Camera& camera)
{
    auto& keyboard = ren::io::devices::Keyboard::getInstance();

    const float speed = 5.0f;

    glm::vec3 position = camera.getPosition();
    glm::vec3 up = camera.getUp();
    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();

    glm::vec3 moveDir(0.0f);

    if (keyboard.isPressed(GLFW_KEY_W))
        moveDir += front;
    if (keyboard.isPressed(GLFW_KEY_S))
        moveDir -= front;
    if (keyboard.isPressed(GLFW_KEY_A))
        moveDir -= right;
    if (keyboard.isPressed(GLFW_KEY_D))
        moveDir += right;
    if (keyboard.isPressed(GLFW_KEY_SPACE))
        moveDir += up;
    if (keyboard.isPressed(GLFW_KEY_LEFT_CONTROL))
        moveDir -= up;

    if (glm::length(moveDir) > 0.0f)
        moveDir = glm::normalize(moveDir);

    position += moveDir * speed * dt;
    camera.setPosition(position);
}