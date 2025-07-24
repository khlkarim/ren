#include <core\\Window.hpp>
#include <components\\meshes\\Cube.hpp>
#include <io/AssetManager.hpp>

int main()
{
    ren::Window window("hi", 1980, 1080);
    ren::Scene scene;
    ren::Camera camera;
    ren::io::AssetManager assetManager; 
    
    std::optional<ren::components::shaders::Shader> shader = assetManager.loadShader("assets\\shaders\\default\\default.vert", "assets\\shaders\\default\\default.frag");

    if(!shader) return -1;

    const std::string player = scene.createEntity();

    ren::components::Transform transform;
    ren::components::meshes::Cube cube;
    ren::components::MeshRenderer meshRenderer(shader.value(), {});
    
    scene.setComponent<ren::components::Transform>(player, transform);
    scene.setComponent<ren::components::Mesh>(player, cube);
    scene.setComponent<ren::components::MeshRenderer>(player, meshRenderer);
    scene.setCamera(camera);

    float lastFrame = glfwGetTime();

    while(window.isOpen()) {
        float currentFrame = glfwGetTime();
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        transform.rotate(30 * delta, glm::vec3(0.0f, 1.0f, 1.0f));
        scene.setComponent<ren::components::Transform>(player, transform);

        window.render(scene);
    }

    return 0;
}