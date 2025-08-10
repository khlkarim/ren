#pragma once

#include "ecs/systems/SystemManager.hpp"
#include "ecs/entities/EntityManager.hpp"

namespace ren::core
{

class Scene 
{
public:
    ecs::entities::EntityManager& getEntityManager();
    const ecs::entities::EntityManager& getEntityManager() const;
    void setEntityManager(const ecs::entities::EntityManager& manager);

    ecs::systems::SystemManager& getSystemManager();
    const ecs::systems::SystemManager& getSystemManager() const;
    void setSystemManager(const ecs::systems::SystemManager& manager);

    // Update all systems
    void update(float deltaTime);

private:
    ecs::entities::EntityManager m_entityManager;
    ecs::systems::SystemManager m_systemManager;
};

}
