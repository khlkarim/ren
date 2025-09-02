#include "ren/core.hpp"
#include "ren/io.hpp"
#include "ren/ecs.hpp"
#include "ren/assets.hpp"
#include "ren/renderer.hpp"

int main()
{
    ren::core::Window window("Primitive Sphere Demo", 1920, 1080);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);

    ren::core::Scene scene;

    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets/shaders/normals/normals.vert", 
        "assets/shaders/normals/normals.frag"
    );

    ren::ecs::entities::Entity mesh;
    auto& componentManager = mesh.getComponentManager();
    componentManager.add<ren::ecs::components::Transform>();
    componentManager.set(ren::ecs::components::MeshRenderer(shader, {}));

    mesh.setId("Sphere");
    componentManager.add<ren::ecs::components::meshes::Sphere>();
    scene.getEntityManager().add(mesh);

    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem cameraSystem;
    renderer.setRenderTarget(window.getGlfwWindow());

    double lastTime = glfwGetTime();
    while (window.isOpen())
    {   
        const double currentTime = glfwGetTime();
        const float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        scene
            .getEntityManager()
            .getComponent<ren::ecs::components::Transform>("Sphere")
            .value().get()
            .rotate(10.0f * deltaTime, glm::vec3(1.0f, 0.0f, 1.0f));

        cameraSystem.update(deltaTime, renderer.getCamera());
        renderer.render(scene);
    }

    return 0;
}