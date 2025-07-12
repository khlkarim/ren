#include "Scene.hpp"

bool Scene::add(Model* model) {
    bool exists = find(this->models.begin(), this->models.end(), model) != this->models.end();
    if (!exists) {
        this->models.push_back(std::move(model));
    }

    spdlog::info("Added model to scene");

    return exists;
}

bool Scene::remove(Model* model) {
    auto it = find(this->models.begin(), this->models.end(), model);
    
    if(it != this->models.end()) {
        this->models.erase(it);
    }

    return it != this->models.end();
}

void Scene::render()
{   
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    for(int i = 0; i < this->models.size(); i++)
    {
        this->models[i]->render(projection, view);
    }
}