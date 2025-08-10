#include <spdlog/spdlog.h>
#include "io/devices/Mouse.hpp"
#include "io/devices/Keyboard.hpp"
#include "io/events/mouse/Moved.hpp"
#include "io/events/mouse/Clicked.hpp"
#include "io/events/keyboard/KeyInput.hpp"
#include "renderer/Camera.hpp"
#include "renderer/CameraSystem.hpp"

namespace ren::renderer {

CameraSystem::CameraSystem() : m_cursorLocked(true)
{
    auto& mouse = io::devices::Mouse::getInstance();
    auto& keyboard = io::devices::Keyboard::getInstance();
    GLFWwindow* window = mouse.getWindow();

    // Initialize cursor state
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Setup keyboard events
    keyboard.on<io::events::keyboard::KeyInput>([window, this](const auto& event) {
        if (event.key == GLFW_KEY_ESCAPE) {
            m_cursorLocked = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    });
    
    // Setup mouse events
    mouse.on<io::events::mouse::Clicked>([window, this](const auto& event) {            
        if (event.action == GLFW_PRESS) {
            m_cursorLocked = true;  
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    });
}

void CameraSystem::update(const float dt, Camera& camera)
{   
    updatePosition(dt, camera);
    if (m_cursorLocked) {
        updateDirection(dt, camera);
    }
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

void CameraSystem::updatePosition(float dt, Camera& camera)
{
    auto& keyboard = io::devices::Keyboard::getInstance();
    const float speed = 5.0f;

    glm::vec3 position = camera.getPosition();
    const glm::vec3 up = camera.getUp();
    const glm::vec3 front = camera.getFront();
    const glm::vec3 right = camera.getRight();

    glm::vec3 moveDir(0.0f);

    if (keyboard.isPressed(GLFW_KEY_W)) {
        moveDir += front;
    }
    if (keyboard.isPressed(GLFW_KEY_S)) {
        moveDir -= front;
    }
    if (keyboard.isPressed(GLFW_KEY_A)) {
        moveDir -= right;
    }
    if (keyboard.isPressed(GLFW_KEY_D)) {
        moveDir += right;
    }
    if (keyboard.isPressed(GLFW_KEY_SPACE)) {
        moveDir += up;
    }
    if (keyboard.isPressed(GLFW_KEY_LEFT_CONTROL)) {
        moveDir -= up;
    }

    if (glm::length(moveDir) > 0.0f) {
        moveDir = glm::normalize(moveDir);
        position += moveDir * speed * dt;
        camera.setPosition(position);
    }
}

}