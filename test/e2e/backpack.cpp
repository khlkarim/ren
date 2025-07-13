#include <iostream>
#include "Window.hpp"
#include "AssetManager.hpp"

int main()
{
    Window window("hi", 1920, 1080);

    AssetManager assetManager;
    std::optional<Model> modelOpt = assetManager.loadModel("assets\\models\\backpack\\backpack.obj");
    std::optional<Shader> shaderOpt = assetManager.loadShader(
        "assets\\shaders\\backpack\\backpack.vert", 
        "assets\\shaders\\backpack\\backpack.frag"
    );

    if(!modelOpt || !shaderOpt)
    {
        spdlog::critical("Failed to load assets");
        exit(-1);
    }

    std::shared_ptr<Model> model(std::make_shared<Model>(*modelOpt));
    std::shared_ptr<Shader> shader(std::make_shared<Shader>(*shaderOpt));

    model->setShader(shader);

    Scene scene;
    scene.add(model);
    
    while(window.isOpen())
    {
        window.render(scene);
    }

    return 0;
}