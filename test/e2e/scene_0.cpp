#include <iostream>
#include "Window.hpp"

int main()
{
    std::string pathToModel = "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\models\\backpack\\backpack.obj";

    Window window("hi", 800, 600);

    Scene scene;
    Model* model = new Model(pathToModel);
    
    scene.add(model);
    
    while(window.isOpen())
    {
        model->transform.setRotation(glm::vec3(0.0f, 10.0f * glfwGetTime(), 0.0f));
        // model->transform.setPosition(glm::vec3(glm::sin(glfwGetTime()), glm::cos(glfwGetTime()), 0.0f));
        window.render(scene);
    }

    return 0;
}