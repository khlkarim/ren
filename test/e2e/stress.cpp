#include "ren/core.hpp"
#include "ren/io.hpp"
#include "ren/ecs.hpp"
#include "ren/assets.hpp"
#include "ren/renderer.hpp"

void fill(ren::core::Scene& scene);

int main()
{
    ren::core::Window window("Stress", 1920, 1080);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);

    ren::core::Scene scene;
    fill(scene);

    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem cameraSystem;
    renderer.setRenderTarget(window.getGlfwWindow());

    double lastTime = glfwGetTime();
    while (window.isOpen())
    {   
        const double currentTime = glfwGetTime();
        const float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        cameraSystem.update(deltaTime, renderer.getCamera());
        renderer.render(scene);
    }

    return 0;
}

void fill(ren::core::Scene& scene)
{
    int count = 1000;

    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets/shaders/normals/normals.vert", 
        "assets/shaders/normals/normals.frag"
    );

    ren::ecs::entities::Entity mesh;
    auto& componentManager = mesh.getComponentManager();
    componentManager.add<ren::ecs::components::Transform>();
    componentManager.add<ren::ecs::components::meshes::Sphere>();
    componentManager.set(ren::ecs::components::MeshRenderer(shader, {}));

    auto& t = componentManager.get<ren::ecs::components::Transform>().value().get();
    for(int i = 0; i<count; i++)
    {
        mesh.setId("Sphere_" + std::to_string(i));
        scene.getEntityManager().add(mesh);

        t.setPosition(t.getPosition() + glm::vec3(1.0f, 0.0f, 0.0f));
    }
}