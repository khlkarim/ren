#include "Scene.hpp"

void Scene::setCamera(Camera& camera) {
    this->camera = camera;
}

bool Scene::add(Model& model) {
    auto it = find(this->models.begin(), this->models.end(), model);
    this->models.push_back(model);

    return it == this->models.end();
}

bool Scene::remove(Model& model) {
    auto it = find(this->models.begin(), this->models.end(), model);
    
    if(it != this->models.end()) {
        this->models.erase(it);
    }

    return it != this->models.end();
}