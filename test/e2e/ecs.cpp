#include <core\\Window.hpp>
#include <components\\meshes\\Cube.hpp>
#include <io/AssetManager.hpp>

int main()
{
    ren::Window window("ecs", 1980, 1080);

    ren::Scene scene;
    // ren::Camera camera;
    // scene.setCamera(camera);

    ren::io::AssetManager assetManager; 
    ren::components::shaders::Shader shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    const std::string player = scene.createEntity();

    ren::components::meshes::Cube cube;
    ren::components::Transform transform;
    ren::components::MeshRenderer meshRenderer(shader, {});
    
    scene.setComponent<ren::components::Mesh>(player, cube);
    scene.setComponent<ren::components::Transform>(player, transform);
    scene.setComponent<ren::components::MeshRenderer>(player, meshRenderer);

    float lastFrame = static_cast<float>(glfwGetTime());

    while(window.isOpen()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& t = scene.getComponent<ren::components::Transform>(player);
        auto& mr = scene.getComponent<ren::components::MeshRenderer>(player);
        auto& s = mr.getShader();

        t.rotate(10 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
        s.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        s.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));
        
        window.render(scene);
    }

    return 0;
}