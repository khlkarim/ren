#pragma once

#include <string>
#include "ecs/entities/EntityManager.hpp"

namespace ren::core
{

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    ecs::entities::EntityManager& getEntityManager();
    const ecs::entities::EntityManager& getEntityManager() const;
    void setEntityManager(const ecs::entities::EntityManager& EntityManager);

private:
    ecs::entities::EntityManager entityManager;
};

}