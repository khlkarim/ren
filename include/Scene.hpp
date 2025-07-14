#pragma once
#include "Camera.hpp"
#include "Model.hpp"

namespace ren {

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

}