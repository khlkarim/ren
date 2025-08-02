#include <core/Window.hpp>
#include <io/InputSystem.hpp>
#include <assets/AssetManager.hpp>
#include <components/meshes/Cube.hpp>
#include <unordered_set>

void updateCameraDirection(ren::Camera& camera, const ren::io::events::mouse::Moved& event, float deltaTime);
void updateCameraPosition(ren::Camera& camera, const ren::io::events::keyboard::KeyInput& event, float deltaTime);

int main()
{
    ren::Window window("Input System Test", 1980, 1080);
    auto& inputSystem = ren::io::InputSystem::listen(window);
    
    bool cursorLocked = true;
    glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    inputSystem.on<ren::io::events::keyboard::KeyInput>([&window, &cursorLocked](const auto& event)
        {
            if(event.key == GLFW_KEY_ESCAPE)
            {
                cursorLocked = false;
                glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        });
    inputSystem.on<ren::io::events::mouse::Clicked>([&window, &cursorLocked](const auto& event)
        {
            if(event.action == GLFW_PRESS)
            {
                cursorLocked = true;
                glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        });

    ren::assets::AssetManager assetManager; 
    auto shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    ren::Scene scene;

    ren::Entity cube;
    cube.setComponent<ren::components::Transform>(ren::components::Transform());
    cube.setComponent<ren::components::Mesh>(ren::components::meshes::Cube());
    cube.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {}));

    auto& camera = scene.getCamera();
    auto& hierarchy = scene.getHierarchy();
    
    cube.setId("cube-1");
    hierarchy.add(cube);
    cube.getComponent<ren::components::Transform>().value().get().setPosition(glm::vec3(0.0f, 0.0f, 12.0f));
    cube.setId("cube-2");
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

        inputSystem.if_active<ren::io::events::mouse::Moved>([&camera, deltaTime, cursorLocked](const auto& event)
            {
                if(cursorLocked) updateCameraDirection(camera, event, deltaTime);
            });

        auto& mr1 = scene.getHierarchy().getComponent<ren::components::MeshRenderer>("cube-1").value().get();
        auto& mr2 = scene.getHierarchy().getComponent<ren::components::MeshRenderer>("cube-2").value().get();
        
        auto& s1 = mr1.getShader();
        auto& s2 = mr2.getShader();

        s1.setVec3("ulightPos", glm::vec3(0.0f, 0.0f, 6.0f));
        s1.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        s2.setVec3("ulightPos", glm::vec3(0.0f, 0.0f, 6.0f));
        s2.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        window.render(scene);
    }

    return 0;
}

void updateCameraPosition(ren::Camera& camera, const ren::io::events::keyboard::KeyInput& event, float deltaTime)
{
    const float speed = 5.0f;

    glm::vec3 position = camera.getPosition();
    glm::vec3 up = camera.getUp();
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
    if (event.key == GLFW_KEY_SPACE)
        position += up * speed * deltaTime;
    if (event.key == GLFW_KEY_LEFT_CONTROL)
        position -= up * speed * deltaTime;

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
