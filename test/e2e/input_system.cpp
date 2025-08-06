#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/io.hpp"
#include "ren/renderer.hpp"

int main()
{
    ren::core::Window window("Input System Test", 1980, 1080);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);
    
    ren::assets::AssetManager assetManager; 
    auto shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    ren::core::Scene scene;

    ren::ecs::entities::Entity cube;
    cube.getComponentManager().set<ren::ecs::components::Transform>(ren::ecs::components::Transform());
    cube.getComponentManager().set<ren::ecs::components::Mesh>(ren::ecs::components::meshes::Cube());
    cube.getComponentManager().set<ren::ecs::components::MeshRenderer>(ren::ecs::components::MeshRenderer(shader, {}));

    auto& hierarchy = scene.getEntityManager();
    cube.setId("cube-1");
    hierarchy.add(cube);
    cube.getComponentManager().get<ren::ecs::components::Transform>().value().get().setPosition(glm::vec3(0.0f, 0.0f, 12.0f));
    cube.setId("cube-2");
    hierarchy.add(cube);
    
    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem cameraSystem;
    renderer.setRenderTarget(window.getGLFWwindow());

    double lastTime = glfwGetTime();
    while(window.isOpen()) 
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        auto& mr1 = scene.getEntityManager().getComponent<ren::ecs::components::MeshRenderer>("cube-1").value().get();
        auto& mr2 = scene.getEntityManager().getComponent<ren::ecs::components::MeshRenderer>("cube-2").value().get();
        
        auto& s1 = mr1.getShader();
        auto& s2 = mr2.getShader();

        s1.setVec3("ulightPos", glm::vec3(0.0f, 0.0f, 6.0f));
        s1.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        s2.setVec3("ulightPos", glm::vec3(0.0f, 0.0f, 6.0f));
        s2.setVec3("ulightColor", glm::vec3(
            glm::cos(glfwGetTime()) * glm::cos(glfwGetTime()), 
            glm::sin(glfwGetTime()) * glm::sin(glfwGetTime()), 
            glm::cos(glfwGetTime() - glm::pi<double>()/4) * glm::cos(glfwGetTime() - glm::pi<double>()/4)
        ));

        cameraSystem.update(deltaTime, renderer.getCamera());
        renderer.render(scene);
    }

    return 0;
}