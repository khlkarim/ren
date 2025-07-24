#include <core\\Window.hpp>
#include <components\\meshes\\Cube.hpp>
#include <io/AssetManager.hpp>

int main()
{
    ren::Window window("ecs", 1980, 1080);

    ren::Scene scene;
    ren::Camera camera;
    scene.setCamera(camera);

    ren::io::AssetManager assetManager; 
    std::optional<ren::components::shaders::Shader> shader = assetManager.loadShader("assets\\shaders\\default\\default.vert", "assets\\shaders\\default\\default.frag");
    if(!shader) return -1;

    const std::string player = scene.createEntity();

    ren::components::meshes::Cube cube;
    ren::components::Transform transform;
    ren::components::MeshRenderer meshRenderer(shader.value(), {});
    
    scene.setComponent<ren::components::Mesh>(player, cube);
    scene.setComponent<ren::components::Transform>(player, transform);
    scene.setComponent<ren::components::MeshRenderer>(player, meshRenderer);

    float lastFrame = glfwGetTime();

    while(window.isOpen()) {
        float currentFrame = glfwGetTime();
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& c = scene.getCamera().value().get();
        auto& t = scene.getComponent<ren::components::Transform>(player).value().get();

        t.rotate(30 * delta, glm::vec3(0.0f, 1.0f, 1.0f));
        c.setPosition(glm::vec3(6.0f * glm::sin(glfwGetTime()), 0.0f, 6.0f * glm::cos(glfwGetTime())));

        window.render(scene);
    }

    return 0;
}