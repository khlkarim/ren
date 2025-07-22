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

const Camera& Scene::getCamera()
{
    return *(this->camera);
}

const std::string& Scene::createEntity()
{   
    const boost::uuids::uuid id_struct = boost::uuids::random_generator()();
    const std::string id = boost::uuids::to_string(id_struct);

    this->entities[id] = std::make_unique<Entity>();
    spdlog::info("Entity with id: {} created", id);

    return id;
}

template<typename T>
void Scene::setComponent(const std::string& id, const T& component)
{
    if (this->entities.find(id) != this->entities.end()) {
        this->entities[id]->setComponent(component);
        spdlog::info("Component added to Entity with id: {}", id);
    } else {
        spdlog::warn("Entity with id: {} does not exist", id);
    }
}

template<typename T>
std::optional<std::reference_wrapper<const T>> Scene::getComponent(const std::string& id) const
{
    if (this->entities.find(id) != this->entities.end()) {
        return this->entities[id]->getComponent<T>();
    } else {
        spdlog::warn("Entity with id: {} does not exist", id);
        return std::nullopt;
    }
}

void Scene::render() const
{
    for(const auto& [id, entity]: this->entities)
    {
    }
}