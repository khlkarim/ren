#include <iostream>
#include "Window.hpp"
#include "AssetManager.hpp"

int main()
{
    ren::Window window("hi", 1920, 1080);

    ren::io::AssetManager assetManager;
    auto modelOpt = assetManager.loadModel("assets\\models\\backpack\\backpack.obj");
    auto shaderOpt = assetManager.loadShader(
        "assets\\shaders\\backpack\\backpack.vert", 
        "assets\\shaders\\backpack\\backpack.frag"
    );

    if(!modelOpt || !shaderOpt)
    {
        spdlog::critical("Failed to load assets");
        exit(-1);
    }

    auto model(std::make_shared<ren::Model>(*modelOpt));
    auto shader(std::make_shared<ren::components::shaders::Shader>(*shaderOpt));

    model->setShader(shader);

    ren::Scene scene;
    scene.add(model);
    
    while(window.isOpen())
    {
        window.render(scene);
    }

    return 0;
}