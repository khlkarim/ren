#include <vector>
#include <string>
#include <unordered_set>
#include "ecs/entities/EntityManager.hpp"
#include "physics/components/Collider.hpp"
#include "physics/systems/PhysicsSystem.hpp"
using ren::ecs::systems::System;
using ren::ecs::components::Transform;
using ren::physics::systems::PhysicsSystem;
using ren::physics::components::Collider;
using ren::physics::components::RigidBody;

void PhysicsSystem::update(const float dt, ecs::entities::EntityManager& entityManager)
{
    std::vector<std::string> entitiesWithCollider = entityManager.getEntitiesWith<Collider>();
    std::vector<std::string> entitiesWithRigidbody = entityManager.getEntitiesWith<RigidBody>();

    std::unordered_set<std::string> entitySet(entitiesWithCollider.begin(), entitiesWithCollider.end());
    entitySet.insert(entitiesWithRigidbody.begin(), entitiesWithRigidbody.end());
    std::vector<std::string> entities(entitySet.begin(), entitySet.end());

    for(const auto& entityId : entitiesWithRigidbody)
    {
        auto& transform = entityManager.getComponent<Transform>(entityId).value().get();
        auto& rigidBody = entityManager.getComponent<RigidBody>(entityId).value().get();

        this->apply(dt, rigidBody, transform);
    }
}

std::unique_ptr<System> PhysicsSystem::clone() const
{
    return std::make_unique<PhysicsSystem>(*this);
}

void PhysicsSystem::apply(const float dt, RigidBody& rigidBody, Transform& transform)
{
    if (rigidBody.getType() != RigidBody::Type::Dynamic || rigidBody.getMass() <= 0.0f)
        return;

    glm::vec3 velocity = rigidBody.getVelocity();
    velocity += (dt * rigidBody.getForce()) / rigidBody.getMass();
    rigidBody.setVelocity(velocity);

    glm::vec3 angularVelocity = rigidBody.getAngularVelocity();
    angularVelocity += (dt * rigidBody.getTorque()) / rigidBody.getInertia();
    rigidBody.setAngularVelocity(angularVelocity);

    rigidBody.clearForces();
    rigidBody.clearTorques();

    glm::vec3 position = transform.getPosition();
    transform.setPosition(position + dt * velocity);

    glm::quat rotation = transform.getRotation();
    glm::quat omega(0.0f, angularVelocity);
    glm::quat dq = 0.5f * omega * rotation;
    rotation += dq * dt;
    transform.setRotation(glm::normalize(rotation));
}