#include <io/InputSystem.hpp>
#include <systems/CameraSystem.hpp>
#include <io/events/mouse/Clicked.hpp>
using ren::systems::CameraSystem;

CameraSystem::CameraSystem()
{
    auto& inputSystem = ren::io::InputSystem::getInstance();
    GLFWwindow* window = inputSystem.getWindow();

    this->cursorLocked = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    inputSystem.on<ren::io::events::keyboard::KeyInput>([window, this](const auto& event)
        {
            if(event.key == GLFW_KEY_ESCAPE)
            {
                this->cursorLocked = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        });
    inputSystem.on<ren::io::events::mouse::Clicked>([window, this](const auto& event)
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
    auto& inputSystem = ren::io::InputSystem::getInstance();

    inputSystem.if_active<ren::io::events::keyboard::KeyInput>([dt, &camera, this](const auto& event)
        {
            this->updatePosition(dt, camera, event);
        });

    inputSystem.if_active<ren::io::events::mouse::Moved>([dt, &camera, this](const auto& event)
        {
            if(this->cursorLocked) this->updateDirection(dt, camera, event);
        });
}

void CameraSystem::updateDirection(const float dt, Camera& camera, const ren::io::events::mouse::Moved& event)
{
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

void CameraSystem::updatePosition(const float dt, Camera& camera, const ren::io::events::keyboard::KeyInput& event)
{
    const float speed = 5.0f;

    glm::vec3 position = camera.getPosition();
    glm::vec3 up = camera.getUp();
    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();

    if (event.key == GLFW_KEY_W)
        position += front * speed * dt;
    if (event.key == GLFW_KEY_S)
        position -= front * speed * dt;
    if (event.key == GLFW_KEY_A)
        position -= right * speed * dt;
    if (event.key == GLFW_KEY_D)
        position += right * speed * dt;
    if (event.key == GLFW_KEY_SPACE)
        position += up * speed * dt;
    if (event.key == GLFW_KEY_LEFT_CONTROL)
        position -= up * speed * dt;

    camera.setPosition(position);
}