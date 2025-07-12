#pragma once

#include <vector>
#include "Camera.hpp"
#include "Model.hpp"

class Scene 
{
public:
    void render();
    bool add(Model* model);
    bool remove(Model* model);

public:
    Camera camera;
    std::vector<Model*> models;
};