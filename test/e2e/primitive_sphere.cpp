#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"

int main()
{
    // Initialize window with descriptive name and standard resolution
    ren::core::Window window("Primitive Sphere Demo", 1920, 1080);
    
    // Create scene to hold entities
    ren::core::Scene scene;

    // Load and manage assets
    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets/shaders/default/default.vert", 
        "assets/shaders/default/default.frag"
    );

    // Create sphere entity with appropriate components
    ren::ecs::entities::Entity sphereEntity("sphere");
    auto& componentManager = sphereEntity.getComponentManager();
    componentManager.add<ren::ecs::components::meshes::Sphere>();
    componentManager.set(ren::ecs::components::MeshRenderer(shader, {}));

    // Add entity to scene
    scene.getEntityManager().add(sphereEntity);

    // Configure renderer
    ren::renderer::Renderer renderer;
    renderer.setRenderTarget(window.getGlfwWindow());

    // Main render loop
    while (window.isOpen())
    {
        renderer.render(scene);
    }

    return 0;
}