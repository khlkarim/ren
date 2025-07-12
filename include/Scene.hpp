#pragma once

#include <vector>
#include <memory>
#include "Camera.hpp"
#include "Model.hpp"

class Scene 
{
public:
    void render();
    bool add(std::shared_ptr<Model> model);
    bool remove(std::shared_ptr<Model> model);

public:
    Camera camera;
    std::vector<std::shared_ptr<Model>> models;
};