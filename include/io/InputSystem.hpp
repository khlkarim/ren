#pragma once

#include <vector>

class InputSystem
{
public:
    InputSystem();
    void on(int event, int handler);
    void off(int handler);

private:
    std::vector<int> callbacks;
};