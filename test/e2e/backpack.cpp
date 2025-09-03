#include "ren/core.hpp"
#include "ren/ecs.hpp"
#include "ren/assets.hpp"
#include "ren/renderer.hpp"
#include "ren/utils.hpp"

namespace {
    // Forward declaration
    void ApplyShaderToEntity(ren::ecs::entities::Entity& entity, ren::ecs::components::shaders::Shader& shader);

    // Constants
    constexpr int WINDOW_WIDTH = 1980;
    constexpr int WINDOW_HEIGHT = 1080;
    constexpr char WINDOW_TITLE[] = "Backpack";
    constexpr char MODEL_PATH[] = "assets\\models\\backpack\\backpack.obj";
    constexpr char VERTEX_SHADER_PATH[] = "assets\\shaders\\backpack\\backpack.vert";
    constexpr char FRAGMENT_SHADER_PATH[] = "assets\\shaders\\backpack\\backpack.frag";
    constexpr float ROTATION_SPEED = 30.0f;
}

int main()
{
    // Initialize core components
    ren::core::Window window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    ren::core::Scene scene;
    ren::assets::AssetManager assetManager;
    ren::renderer::Renderer renderer;
    
    // Load and setup the entity
    auto entity = assetManager.loadEntity(MODEL_PATH);
    entity.getComponentManager().add<ren::ecs::components::Transform>();
    
    // Load and apply shader
    auto shader = assetManager.loadShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    ApplyShaderToEntity(entity, shader);

    // Add entity to scene
    auto& entityManager = scene.getEntityManager();
    entityManager.add(entity);

    // Setup renderer
    renderer.setRenderTarget(window.getGlfwWindow());

    // Main loop
    ren::utils::Timer timer;
    timer.start();
    
    while(window.isOpen()) {
        timer.update();

        // Calculate delta time
        float deltaTime = static_cast<float>(timer.getDeltaTime());

        // Update entity rotation
        auto& transform = entityManager.getComponent<ren::ecs::components::Transform>(entity.getId())
                          .value().get();
        transform.rotate(ROTATION_SPEED * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

        // Render frame
        renderer.render(scene);
    }

    return 0;
}

namespace {
    void ApplyShaderToEntity(ren::ecs::entities::Entity& entity, ren::ecs::components::shaders::Shader& shader)
    {
        auto& componentManager = entity.getComponentManager();

        // Apply shader to mesh renderer if present
        if(componentManager.has<ren::ecs::components::MeshRenderer>()) {
            auto& meshRenderer = componentManager.get<ren::ecs::components::MeshRenderer>().value().get();
            meshRenderer.setShader(shader);
        }

        // Recursively apply shader to all children
        if(componentManager.has<ren::ecs::components::Hierarchy>()) {
            auto& hierarchy = componentManager.get<ren::ecs::components::Hierarchy>().value().get();
            const std::vector<std::string>& children = hierarchy.getChildren();

            for(const auto& childId : children) {
                if(auto childEntity = hierarchy.get(childId)) {
                    ApplyShaderToEntity(childEntity.value(), shader);
                }
            }
        }
    }
}