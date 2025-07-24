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

std::optional<std::reference_wrapper<Camera>> Scene::getCamera() const
{
    if(this->camera)
    {
        return *(this->camera);
    }
    else 
    {
        spdlog::warn("Scene has no camera");
        return std::nullopt;
    }
}

std::string Scene::createEntity()
{   
    const boost::uuids::uuid id_struct = boost::uuids::random_generator()();
    const std::string id = boost::uuids::to_string(id_struct);

    this->entities[id] = std::make_unique<Entity>();
    spdlog::info("Entity with id: {} created", id);

    return id;
}

void Scene::render() const
{
    ren::systems::RenderingSystem renderingSystem;

    for(const auto& [id, entity]: this->entities)
    {
        renderingSystem.render(*this->camera, *entity);
    }
}