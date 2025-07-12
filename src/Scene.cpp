#include "Scene.hpp"

bool Scene::add(std::shared_ptr<Model> model) {
    if (!model) return false;

    for (const auto& m : models) {
        if (m == model) return false;
    }

    models.push_back(model);
    return true;
}

bool Scene::remove(std::shared_ptr<Model> model) {
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