#include <iostream>
#include "Window.hpp"

int main()
{
    Window window("Scene 0", 800, 600);

    while(window.isOpen()) {
        window.render();
    }

    return 0;
}