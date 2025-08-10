#include "ecs/components/Transform.hpp"
#include "physics/components/RigidBody.hpp"
#include "physics/systems/dynamics/Solver.hpp"

namespace ren::physics::systems::dynamics {

void Solver::solve(float dt, components::RigidBody& rigidBody, ecs::components::Transform& transform) 
{
    // Skip non-dynamic or massless bodies
    if (rigidBody.getType() != components::RigidBody::Type::Dynamic || rigidBody.getMass() <= 0.0f) {
        return;
    }

    // Update linear velocity from forces
    glm::vec3 velocity = rigidBody.getVelocity();
    velocity += dt * rigidBody.getForce() / rigidBody.getMass();
    rigidBody.setVelocity(velocity);

    // Update angular velocity from torques
    glm::vec3 angularVelocity = rigidBody.getAngularVelocity();
    angularVelocity += dt * rigidBody.getTorque() / rigidBody.getInertia();
    rigidBody.setAngularVelocity(angularVelocity);

    // Clear accumulated forces and torques
    rigidBody.clearForces();
    rigidBody.clearTorques();

    // Update position based on velocity
    glm::vec3 position = transform.getPosition();
    transform.setPosition(position + dt * velocity);

    // Update rotation based on angular velocity
    // Using quaternion integration: dq/dt = 0.5 * omega * q
    glm::quat rotation = transform.getRotation();
    glm::quat omega(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z);
    rotation += 0.5f * omega * rotation * dt;
    transform.setRotation(glm::normalize(rotation));
}

} 