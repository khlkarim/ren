#include "core/Scene.hpp"
using ren::core::Scene;
using ren::ecs::entities::EntityManager;
using ren::ecs::systems::SystemManager;

Scene::Scene()
{   
    spdlog::info("Scene Constructor");
}

Scene::~Scene()
{
    spdlog::info("Scene Destructor");
}

EntityManager& Scene::getEntityManager()
{
    return this->entityManager;
}

const EntityManager& Scene::getEntityManager() const
{
    return this->entityManager;
}

void Scene::setEntityManager(const EntityManager& entityManager)
{
    this->entityManager = entityManager;
    spdlog::info("EntityManager set");
}

SystemManager& Scene::getSystemManager()
{
    return this->systemManager;
}

const SystemManager& Scene::getSystemManager() const
{
    return this->systemManager;
}

void Scene::setSystemManager(const SystemManager& systemManager)
{
    this->systemManager = systemManager;
    spdlog::info("SystemManager set");
}

void Scene::update(const float dt)
{
    this->systemManager.update(dt, this->entityManager);
}