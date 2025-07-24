#include <core/Scene.hpp>
using ren::Scene;
using ren::Camera; 
using ren::Entity; 

Scene::Scene()
{   
    spdlog::info("Scene Constructor");
}

Scene::~Scene()
{
    spdlog::info("Scene Destructor");
}

void Scene::setCamera(const Camera& camera)
{
    if (!this->camera) {
        this->camera = std::make_unique<Camera>(camera);
    } else {
        *this->camera = camera;
    }
    spdlog::info("Camera set");
}

Camera& Scene::getCamera()
{
    if(!this->camera)
    {
        fatal("Scene camera is not defined");
    }
    return *(this->camera);
}

void Scene::instantiate(const Entity& entity)
{   
    this->entities[entity.getId()] = std::make_unique<Entity>(entity);
    spdlog::info("Entity with id: {} instantiated", entity.getId());
}

void Scene::remove(const std::string& id)
{
    if(this->entities.find(id) == this->entities.end())
    {
        spdlog::warn("Entity with Id: {} not found", id);
        return;
    }

    this->entities[id].reset(nullptr);
    this->entities.erase(id);
}

void Scene::render() const
{
    if(!this->camera)
    {
        fatal("Scene camera is not defined");
    }
    ren::systems::RenderingSystem renderingSystem;

    for(const auto& [id, entity]: this->entities)
    {
        renderingSystem.render(*this->camera, *entity);
    }
}