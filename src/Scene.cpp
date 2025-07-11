#include "Scene.hpp"

bool Scene::add(Model& model) {
    bool exists = find(this->models.begin(), this->models.end(), model) == this->models.end();
    this->models.push_back(model);

    spdlog::info("Added model to scene");

    return exists;
}

bool Scene::remove(Model& model) {
    auto it = find(this->models.begin(), this->models.end(), model);
    
    if(it != this->models.end()) {
        this->models.erase(it);
    }

    return it != this->models.end();
}

void Scene::render()
{   
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view(1.0f);

    view = glm::translate(view, -camera.position);
    glm::quat q = glm::quat(glm::radians(-camera.direction));
    view *= glm::mat4_cast(q);

    for(int i = 0; i < this->models.size(); i++)
    {
        this->models[i].render(projection, view);
    }
}