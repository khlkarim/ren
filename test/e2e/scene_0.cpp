#include <iostream>
#include "Window.hpp"

int main()
{
    std::string pathToModel = "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\models\\backpack\\backpack.obj";

    Window window("hi", 1920, 1080);

    Scene scene;
    Model* model = new Model(pathToModel);
    
    scene.add(model);
    
    while(window.isOpen())
    {
        model->transform.setRotation(glm::vec3(50.0f * glfwGetTime(), 50.0f * glfwGetTime(), 0.0f));
        model->transform.setPosition(glm::vec3(glm::sin(glfwGetTime()), glm::cos(glfwGetTime()), glm::cos(glfwGetTime())));
        window.render(scene);
    }

    return 0;
}