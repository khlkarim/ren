#include "Scene.hpp"

bool Scene::add(std::shared_ptr<Model> model) {
    if (!model) return false;

    if (std::find(models.begin(), models.end(), model) == models.end()) {
        models.push_back(model);
        return true;
    }

    return false;
}

bool Scene::remove(std::shared_ptr<Model> model) {
    if(!model) return false;

    auto it = std::find(models.begin(), models.end(), model);
    if (it != models.end()) {
        models.erase(it);
        return true;
    }

    return false;
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