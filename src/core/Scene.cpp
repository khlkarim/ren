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

const Camera& Scene::getCamera() const
{
    if(!this->camera)
    {
        fatal("Scene camera is not defined");
    }
    return *(this->camera);
}

Entity& Scene::getEntity(const std::string& id)
{
    if(this->entities.find(id) == this->entities.end())
    {
        fatal("Entity with given id does not exist");
    }
    return *(this->entities[id]);
}

void Scene::instantiate(const Entity& entity)
{   
    if(entity.getId().length() == 0)
    {
        fatal("Entity has no ID");
    }
    if(this->entities.find(entity.getId()) != this->entities.end())
    {
        fatal("An Entity with the same ID already exists");
    }

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