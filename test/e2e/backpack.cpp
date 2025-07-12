#include <iostream>
#include "Window.hpp"

int main()
{
    std::string pathToModel = "assets\\models\\backpack\\backpack.obj";

    Window window("hi", 1920, 1080);

    Scene scene;
    Model* model = new Model(pathToModel);
    
    scene.add(model);
    
    while(window.isOpen())
    {
        scene.camera.setPosition(glm::vec3(6.0f * glm::sin(static_cast<float>(glfwGetTime())), 0.0f, 6.0f * glm::cos(static_cast<float>(glfwGetTime()))));
        window.render(scene);
    }

    return 0;
}