#include <core/Scene.hpp>
#include <core/Window.hpp>
#include <components/meshes/Cube.hpp>
#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <components/MeshRenderer.hpp>
#include <assets/AssetManager.hpp>

int main()
{
    ren::Window window("ecs", 1980, 1080);
    ren::Scene scene;

    ren::assets::AssetManager assetManager; 
    ren::components::shaders::Shader shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    ren::Entity player;
    
    ren::components::meshes::Cube cube;
    ren::components::Transform transform;
    ren::components::Hierarchy hierarchy;
    ren::components::MeshRenderer meshRenderer(shader, {});
    
    player.setComponent<ren::components::Mesh>(cube);
    player.setComponent<ren::components::Transform>(transform);
    player.setComponent<ren::components::MeshRenderer>(meshRenderer);
    player.setComponent<ren::components::Hierarchy>(hierarchy);
    
    player.setId("player1");
    scene.getHierarchy().add(player);

    float lastFrame = static_cast<float>(glfwGetTime());

    auto& h = scene.getHierarchy().getComponent<ren::components::Hierarchy>("player1").value().get();
    player.setId("player2");
    h.add(player);

    while(window.isOpen()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& t1 = scene.getHierarchy().getComponent<ren::components::Transform>("player1").value().get();
        auto& mr1 = scene.getHierarchy().getComponent<ren::components::MeshRenderer>("player1").value().get();
        auto& s1 = mr1.getShader();

        t1.rotate(50 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
        s1.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        s1.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        auto& t2 = h.getComponent<ren::components::Transform>("player2").value().get();
        auto& mr2 = h.getComponent<ren::components::MeshRenderer>("player2").value().get();
        auto& s2 = mr1.getShader();

        t2.rotate(50 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
        t2.setPosition(glm::vec3(1.0f, 0.0f, 1.0f));
        s2.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        s2.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));
        
        window.render(scene);
    }

    return 0;
}