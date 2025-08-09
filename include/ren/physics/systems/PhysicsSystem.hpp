#pragma once

#include "ecs/systems/System.hpp"

namespace ren::physics::systems
{

class PhysicsSystem : public ecs::systems::System
{
public:
    void update(const float dt, ecs::entities::EntityManager& entityManager);
    std::unique_ptr<System> clone() const;

private:
    void handleCollisions(const float dt, ecs::entities::EntityManager& entityManager);
    void updateDynamics(const float dt, ecs::entities::EntityManager& entityManager);
};

}