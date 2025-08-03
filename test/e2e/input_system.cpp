#include <core/Scene.hpp>
#include <core/Window.hpp>
#include <assets/AssetManager.hpp>
#include <io/InputSystem.hpp>
#include <components/meshes/Cube.hpp>
#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <components/MeshRenderer.hpp>
#include <systems/CameraSystem.hpp>

int main()
{
    ren::Window window("Input System Test", 1980, 1080);
    ren::io::InputSystem::listen(window);
    
    ren::systems::CameraSystem cameraSystem;

    ren::assets::AssetManager assetManager; 
    auto shader = assetManager.loadShader("assets\\shaders\\lighting\\lighting.vert", "assets\\shaders\\lighting\\lighting.frag");

    ren::Scene scene;

    ren::Entity cube;
    cube.setComponent<ren::components::Transform>(ren::components::Transform());
    cube.setComponent<ren::components::Mesh>(ren::components::meshes::Cube());
    cube.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {}));

    auto& camera = scene.getCamera();
    auto& hierarchy = scene.getHierarchy();
    
    cube.setId("cube-1");
    hierarchy.add(cube);
    cube.getComponent<ren::components::Transform>().value().get().setPosition(glm::vec3(0.0f, 0.0f, 12.0f));
    cube.setId("cube-2");
    hierarchy.add(cube);
    
    double lastTime = glfwGetTime();
    while(window.isOpen()) 
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        cameraSystem.update(deltaTime, scene.getCamera());

        auto& mr1 = scene.getHierarchy().getComponent<ren::components::MeshRenderer>("cube-1").value().get();
        auto& mr2 = scene.getHierarchy().getComponent<ren::components::MeshRenderer>("cube-2").value().get();
        
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

        window.render(scene);
    }

    return 0;
}