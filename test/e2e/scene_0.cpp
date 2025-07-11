#include <iostream>
#include "Window.hpp"

int main()
{
    std::string pathToModel = "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\models\\backpack\\backpack.obj";

    Window window("hi", 800, 600);

    Scene scene;
    Model model(pathToModel);
    
    model.transform.rotate(glm::vec3(0.0f, 0.0f, 90.0f));
    scene.add(model);
    
    while(window.isOpen())
    {
        window.render(scene);
    }

    return 0;
}