#include <iostream>
#include "Window.hpp"
#include "AssetManager.hpp"

int main()
{
    // std::string pathToModel = "assets\\models\\backpack\\backpack.obj";

    Window window("hi", 1920, 1080);
    AssetManager assetManager;
    std::optional<Model> model = assetManager.loadModel("assets\\models\\backpack\\backpack.obj");

    if(model.has_value()) 
    {
        Scene scene;
        scene.add(std::make_shared<Model>(model.value()));
        
        while(window.isOpen())
        {
            // scene.camera.setPosition(glm::vec3(6.0f * glm::sin(static_cast<float>(glfwGetTime())), 0.0f, 6.0f * glm::cos(static_cast<float>(glfwGetTime()))));
            window.render(scene);
        }

    }


    return 0;
}