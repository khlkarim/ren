#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"
#include "ren/utils.hpp"

namespace {
    // Helper function to update shader lighting parameters
    void updateShaderLighting(ren::ecs::components::shaders::Shader& shader, float time) {
        shader.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        shader.setVec3("ulightColor", glm::vec3(
            glm::cos(time) * glm::cos(time), 
            glm::sin(time) * glm::sin(time), 
            glm::cos(time - glm::pi<double>()/4) * glm::cos(time - glm::pi<double>()/4)
        ));
    }
}

int main()
{
    // Initialize window and scene
    ren::core::Window window("ecs", 1980, 1080);
    ren::core::Scene scene;
    
    // Set up asset manager and load shader
    ren::assets::AssetManager assetManager; 
    auto& shader = assetManager.loadShader(
        "assets\\shaders\\lighting\\lighting.vert", 
        "assets\\shaders\\lighting\\lighting.frag"
    );

    // Set up entity manager
    auto& entityManager = scene.getEntityManager();
    
    // Create parent entity
    ren::ecs::entities::Entity parentEntity;
    auto& parentComponents = parentEntity.getComponentManager();
    
    parentComponents.add<ren::ecs::components::meshes::Cube>();
    parentComponents.add<ren::ecs::components::Transform>();
    parentComponents.add<ren::ecs::components::Hierarchy>();
    parentComponents.set(ren::ecs::components::MeshRenderer(shader, {}));
    
    parentEntity.setId("player1");
    entityManager.add(parentEntity);

    // Create child entity
    auto& hierarchy = entityManager.getComponent<ren::ecs::components::Hierarchy>("player1").value().get();
    
    ren::ecs::entities::Entity childEntity;
    auto& childComponents = childEntity.getComponentManager();
    
    childComponents.add<ren::ecs::components::meshes::Cube>();
    childComponents.add<ren::ecs::components::Transform>();
    childComponents.set(ren::ecs::components::MeshRenderer(shader, {}));
    
    childEntity.setId("player2");
    hierarchy.add(childEntity);
    
    // Initialize renderer
    ren::renderer::Renderer renderer;
    renderer.setRenderTarget(window.getGlfwWindow());
    
    // Main loop
    ren::utils::Timer timer;
    timer.start();
    
    while(window.isOpen()) {
        timer.update();

        // Update parent entity
        auto& parentTransform = entityManager.getComponent<ren::ecs::components::Transform>("player1").value().get();
        auto& parentRenderer = entityManager.getComponent<ren::ecs::components::MeshRenderer>("player1").value().get();
        auto& parentShader = parentRenderer.getShader();

        parentTransform.rotate(50.0f * timer.getDeltaTime(), glm::vec3(1.0f, 0.0f, 1.0f));
        updateShaderLighting(parentShader, timer.getElapsedTime());

        // Update child entity
        auto& childEntity = hierarchy.get("player2").value().get();
        auto& childTransform = childEntity.getComponentManager().get<ren::ecs::components::Transform>().value().get();
        auto& childRenderer = childEntity.getComponentManager().get<ren::ecs::components::MeshRenderer>().value().get();
        auto& childShader = childRenderer.getShader();

        childTransform.rotate(50.0f * timer.getDeltaTime(), glm::vec3(1.0f, 0.0f, 1.0f));
        childTransform.setPosition(glm::vec3(1.0f, 0.0f, 1.0f));
        updateShaderLighting(childShader, timer.getElapsedTime());
        
        // Render scene
        renderer.render(scene);
    }

    return 0;
}