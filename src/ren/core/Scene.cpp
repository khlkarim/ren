#include "core/Scene.hpp"

namespace ren::core {

ecs::entities::EntityManager& Scene::getEntityManager()
{
    return m_entityManager;
}

const ecs::entities::EntityManager& Scene::getEntityManager() const
{
    return m_entityManager;
}

void Scene::setEntityManager(const ecs::entities::EntityManager& entityManager)
{
    m_entityManager = entityManager;
}

ecs::systems::SystemManager& Scene::getSystemManager()
{
    return m_systemManager;
}

const ecs::systems::SystemManager& Scene::getSystemManager() const
{
    return m_systemManager;
}

void Scene::setSystemManager(const ecs::systems::SystemManager& systemManager)
{
    m_systemManager = systemManager;
}

void Scene::update(const float dt)
{
    m_systemManager.update(dt, m_entityManager);
}

}