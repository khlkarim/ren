#include <iostream>
#include "Window.hpp"

int main()
{
    std::string pathToModel = "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\models\\backpack\\backpack.obj";

    Window window("hi", 800, 600);

    Scene scene;
    Model model(pathToModel);
    
    scene.add(model);

    while(window.isOpen())
    {
        window.render(scene);
    }

    return 0;
}