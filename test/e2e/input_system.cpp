#include <core/Window.hpp>
#include <io/InputSystem.hpp>
#include <assets/AssetManager.hpp>
#include <components/meshes/Cube.hpp>
#include <unordered_set>

void updateCameraPosition(ren::Camera& camera, const std::unordered_set<int>& keysDown, float deltaTime);

int main()
{
    ren::Window window("Input System Test", 1980, 1080);
    auto& inputSystem = ren::io::InputSystem::listen(window);

    std::unordered_set<int> keysDown;

    inputSystem.on<ren::io::events::keyboard::KeyInput>(
        [&keysDown](const ren::io::events::keyboard::KeyInput& event) {
            if (event.action == GLFW_PRESS)
                keysDown.insert(event.key);
            else if (event.action == GLFW_RELEASE)
                keysDown.erase(event.key);
        }
    );

    ren::io::AssetManager assetManager; 
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

        updateCameraPosition(camera, keysDown, deltaTime);
        window.render(scene);
    }

    return 0;
}

void updateCameraPosition(ren::Camera& camera, const std::unordered_set<int>& keysDown, float deltaTime)
{
    const float speed = 5.0f;
    glm::vec3 direction(0.0f);

    if (keysDown.count(GLFW_KEY_W)) direction.z -= 1.0f;
    if (keysDown.count(GLFW_KEY_S)) direction.z += 1.0f;
    if (keysDown.count(GLFW_KEY_A)) direction.x -= 1.0f;
    if (keysDown.count(GLFW_KEY_D)) direction.x += 1.0f;

    if (glm::length(direction) > 0.0f)
    {
        direction = glm::normalize(direction);
        camera.setPosition(camera.getPosition() + direction * speed * deltaTime);
    }
}