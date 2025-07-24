#include <core/Window.hpp>
#include <components/meshes/Cube.hpp>
#include <io/AssetManager.hpp>

int main()
{
    ren::Window window("ecs", 1980, 1080);

    ren::Scene scene;
    ren::Camera camera;
    scene.setCamera(camera);

    ren::io::AssetManager assetManager; 
    ren::components::shaders::Shader shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    ren::Entity player;
    
    ren::components::meshes::Cube cube;
    ren::components::Transform transform;
    ren::components::MeshRenderer meshRenderer(shader, {});
    
    player.setComponent<ren::components::Mesh>(cube);
    player.setComponent<ren::components::Transform>(transform);
    player.setComponent<ren::components::MeshRenderer>(meshRenderer);
    
    player.setId("player1");
    scene.instantiate(player);
    player.setId("player2");
    scene.instantiate(player);

    float lastFrame = static_cast<float>(glfwGetTime());

    while(window.isOpen()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& t1 = scene.getComponent<ren::components::Transform>("player1");
        auto& mr1 = scene.getComponent<ren::components::MeshRenderer>("player1");
        auto& s1 = mr1.getShader();

        t1.rotate(10 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
        s1.setVec3("ulightPos", glm::vec3(6.0f, 0.0f, 6.0f));
        s1.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        auto& t2 = scene.getComponent<ren::components::Transform>("player2");
        auto& mr2 = scene.getComponent<ren::components::MeshRenderer>("player2");
        auto& s2 = mr1.getShader();

        t2.rotate(50 * delta, glm::vec3(1.0f, 0.0f, 1.0f));
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