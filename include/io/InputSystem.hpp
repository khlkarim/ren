#pragma once
#include <vector>

namespace ren::io {

class InputSystem
{
public:
    InputSystem();
    void on(int event, int handler);
    void off(int handler);

private:
    std::vector<int> callbacks;
};

}