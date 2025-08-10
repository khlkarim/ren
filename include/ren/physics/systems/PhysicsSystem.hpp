#pragma once

#include "ecs/systems/System.hpp"

namespace ren::physics::systems
{

class PhysicsSystem : public ecs::systems::System
{
public:
    void update(float dt, ecs::entities::EntityManager& entityManager);
    std::unique_ptr<System> clone() const;

private:
    void handleCollisions(float dt, ecs::entities::EntityManager& entityManager);
    void updateDynamics(float dt, ecs::entities::EntityManager& entityManager);
};

}