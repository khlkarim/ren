#pragma once

#include "ecs/systems/System.hpp"
#include "ecs/components/Transform.hpp"
#include "physics/components/RigidBody.hpp"

namespace ren::physics::systems
{

class PhysicsSystem : public ecs::systems::System
{
public:
    void update(const float dt, ecs::entities::EntityManager& entityManager);
    std::unique_ptr<System> clone() const;

private:
    void apply(const float dt, components::RigidBody& rigidBody, ecs::components::Transform& transform);
};

}