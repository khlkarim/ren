#include <core/Window.hpp>
#include <io/InputSystem.hpp>
#include <assets/AssetManager.hpp>
#include <components/meshes/Cube.hpp>
#include <unordered_set>
#include <thread>
#include <chrono>

void updateCameraDirection(ren::Camera& camera, const ren::io::events::mouse::Moved& event, float deltaTime);
void updateCameraPosition(ren::Camera& camera, const ren::io::events::keyboard::KeyInput& event, float deltaTime);

int main()
{
    ren::Window window("Input System Test", 1980, 1080);
    window.setTargetFPS(60);
    
    auto& inputSystem = ren::io::InputSystem::listen(window);
    
    glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    inputSystem.on<ren::io::events::keyboard::KeyInput>([&window](const auto& event)
        {
            if(event.key == GLFW_KEY_ESCAPE)
            {
                glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        });
    inputSystem.on<ren::io::events::mouse::Clicked>([&window](const auto& event)
        {
            if(event.action == GLFW_PRESS)
                glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        });

    ren::assets::AssetManager assetManager; 
    auto shader = assetManager.loadShader("assets\\shaders\\default\\default.vert", "assets\\shaders\\default\\default.frag");

    ren::Scene scene;

    ren::Entity cube("cube");
    cube.setComponent<ren::components::Transform>(ren::components::Transform());
    cube.setComponent<ren::components::Mesh>(ren::components::meshes::Cube());
    cube.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {}));

    auto& camera = scene.getCamera();
    auto& hierarchy = scene.getHierarchy();
    hierarchy.add(cube);
    
    double lastTime = glfwGetTime();
    while(window.isOpen()) 
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        inputSystem.if_active<ren::io::events::keyboard::KeyInput>([&camera, deltaTime](const auto& event)
            {
                updateCameraPosition(camera, event, deltaTime);
            });

        inputSystem.if_active<ren::io::events::mouse::Moved>([&camera, deltaTime](const auto& event)
            {
                updateCameraDirection(camera, event, deltaTime);
            });

        window.render(scene);
    }

    return 0;
}

void updateCameraPosition(ren::Camera& camera, const ren::io::events::keyboard::KeyInput& event, float deltaTime)
{
    const float speed = 5.0f;

    glm::vec3 position = camera.getPosition();
    glm::vec3 front = camera.getFront();
    glm::vec3 right = camera.getRight();

    if (event.key == GLFW_KEY_W)
        position += front * speed * deltaTime;
    if (event.key == GLFW_KEY_S)
        position -= front * speed * deltaTime;
    if (event.key == GLFW_KEY_A)
        position -= right * speed * deltaTime;
    if (event.key == GLFW_KEY_D)
        position += right * speed * deltaTime;

    camera.setPosition(position);
}

void updateCameraDirection(ren::Camera& camera, const ren::io::events::mouse::Moved& event, float deltaTime)
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
    xoffset *= sensitivity * deltaTime;
    yoffset *= sensitivity * deltaTime;

    camera.setYaw(camera.getYaw() + xoffset);
    camera.setPitch(camera.getPitch() + yoffset);
}
