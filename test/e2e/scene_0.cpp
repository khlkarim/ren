#include <iostream>
#include "Window.hpp"

int main()
{
    Window window("Window0", 800, 600);
    
    Scene scene;
    Model model;

    scene.add(model);

    while(window.isOpen()) {
        window.render(scene);
    }

    return 0;
}