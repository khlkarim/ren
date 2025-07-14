#include "Cube.hpp"
#include "Window.hpp"
#include "AssetManager.hpp"
#include "components/meshes/Cube.hpp"

int main()
{
    ren::Window window("Lighting", 1980, 1080);
    ren::Scene scene;

    ren::io::AssetManager assetManager;
    auto shaderOpt = assetManager.loadShader(
        "assets\\shaders\\lighting\\lighting.vert",
        "assets\\shaders\\lighting\\lighting.frag"
    );

    if(!shaderOpt) 
    {
        spdlog::critical("Failed to load shader");
        exit(-1);
    }

    auto shader(std::make_shared<ren::components::shaders::Shader>(*shaderOpt));

    auto cube(std::make_shared<ren::components::meshes::Cube>(ren::components::meshes::Cube()));
    cube->setShader(shader);

    auto model(std::make_shared<ren::Model>(ren::Model()));
    model->addMesh(cube);
    
    scene.add(model);

    float lastFrame = glfwGetTime();
    
    while(window.isOpen())
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        model->transform.rotate(10.f * deltaTime, glm::vec3(1.0f));
        shader->setVec3("ulightPos", glm::vec3(20.0f * cos(glfwGetTime()), 0.0f, 20.0f * sin(glfwGetTime())));        
    
        window.render(scene);
    }

    return 0;
}