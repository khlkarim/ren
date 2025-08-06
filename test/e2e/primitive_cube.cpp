#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"

int main()
{
    ren::core::Window window("ecs", 1980, 1080);
    ren::core::Scene scene;

    ren::assets::AssetManager assetManager; 
    ren::ecs::components::shaders::Shader shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    ren::ecs::entities::Entity player;
    
    ren::ecs::components::meshes::Cube cube;
    ren::ecs::components::Transform transform;
    ren::ecs::components::Hierarchy hierarchy;
    ren::ecs::components::MeshRenderer meshRenderer(shader, {});
    
    player.getComponentManager().set<ren::ecs::components::Mesh>(cube);
    player.getComponentManager().set<ren::ecs::components::Transform>(transform);
    player.getComponentManager().set<ren::ecs::components::MeshRenderer>(meshRenderer);
    player.getComponentManager().set<ren::ecs::components::Hierarchy>(hierarchy);
    
    player.setId("player1");
    scene.getEntityManager().add(player);

    float lastFrame = static_cast<float>(glfwGetTime());

    auto& h = scene.getEntityManager().getComponent<ren::ecs::components::Hierarchy>("player1").value().get();
    player.setId("player2");
    h.add(player);

    ren::renderer::Renderer renderer;
    renderer.setRenderTarget(window.getGLFWwindow());

    while(window.isOpen()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& t1 = scene.getEntityManager().getComponent<ren::ecs::components::Transform>("player1").value().get();
        auto& mr1 = scene.getEntityManager().getComponent<ren::ecs::components::MeshRenderer>("player1").value().get();
        auto& s1 = mr1.getShader();

        t1.rotate(50 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
        s1.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        s1.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        auto& t2 = h.getComponent<ren::ecs::components::Transform>("player2").value().get();
        auto& mr2 = h.getComponent<ren::ecs::components::MeshRenderer>("player2").value().get();
        auto& s2 = mr1.getShader();

        t2.rotate(50 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
        t2.setPosition(glm::vec3(1.0f, 0.0f, 1.0f));
        s2.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        s2.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));
        
        renderer.render(scene);
    }

    return 0;
}