#include "ecs/systems/SystemManager.hpp"

namespace ren::ecs::systems {

SystemManager::SystemManager(const SystemManager& other)
{
    for (const auto& system : other.m_systems)
    {
        m_systems.push_back(system->clone());
    }
}

SystemManager& SystemManager::operator=(const SystemManager& other)
{
    if (this != &other)
    {
        m_systems.clear();
        for (const auto& system : other.m_systems)
        {
            m_systems.push_back(system->clone());
        }
    }
    return *this;
}

void SystemManager::update(float dt, entities::EntityManager& entityManager)
{
    for (const auto& system : m_systems)
    {
        system->update(dt, entityManager);
    }
}

}