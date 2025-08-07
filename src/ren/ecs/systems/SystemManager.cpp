#include "ecs/systems/SystemManager.hpp"
using ren::ecs::systems::SystemManager;

SystemManager::SystemManager(const SystemManager& other)
{
    for(const auto& system: other.systems)
    {
        this->systems.push_back(system->clone());
    }
}

SystemManager& SystemManager::operator=(const SystemManager& other)
{
    if (this != &other)
    {
        this->systems.clear();
        for (const auto& system : other.systems)
        {
            this->systems.push_back(system->clone());
        }
    }
    return *this;
}

void SystemManager::update(const float dt, entities::EntityManager& entityManager)
{
    for(const auto& system: this->systems)
    {
        system->update(dt, entityManager);
    }
}