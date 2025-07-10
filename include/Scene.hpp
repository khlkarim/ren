#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Camera.hpp"
#include "Model.hpp"

class Scene 
{
public:
    void setCamera(Camera& camera);
    bool add(Model& model);
    bool remove(Model& model);

private:    
    Camera camera;
    std::vector<Model> models;
};

#endif // SCENE_HPP