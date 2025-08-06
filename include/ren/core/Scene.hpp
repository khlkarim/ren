#pragma once

#include <string>
#include "ecs/entities/EntityManager.hpp"
#include "ecs/systems/SystemManager.hpp"

namespace ren::core
{

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    ecs::entities::EntityManager& getEntityManager();
    const ecs::entities::EntityManager& getEntityManager() const;
    void setEntityManager(const ecs::entities::EntityManager& entityManager);

    ecs::systems::SystemManager& getSystemManager();
    const ecs::systems::SystemManager& getSystemManager() const;
    void setSystemManager(const ecs::systems::SystemManager& systemManager);

    void update(const float dt);

private:
    ecs::entities::EntityManager entityManager;
    ecs::systems::SystemManager systemManager;
};

}