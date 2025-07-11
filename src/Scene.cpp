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
    std::string vertexShader = "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\shaders\\default.vert";
    std::string fragShader = "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\shaders\\default.frag";

    Shader shader(vertexShader, fragShader);
    shader.use();

    for(int i = 0; i<this->models.size(); i++)
    {
        this->models[i].render(shader);
    }
}