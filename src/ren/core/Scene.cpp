#include "core/Scene.hpp"
using ren::core::Scene;
using ren::ecs::entities::EntityManager;

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