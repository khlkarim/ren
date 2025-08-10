#include "physics/components/RigidBody.hpp"

namespace ren::physics::components {

RigidBody::RigidBody(
    Type type, 
    float mass, 
    const glm::vec3& inertia,
    const glm::vec3& velocity,
    const glm::vec3& force,
    const glm::vec3& angularVelocity,
    const glm::vec3& torque,
    float restitution
) : m_type(type),
    m_mass(mass),
    m_inertia(inertia),
    m_velocity(velocity),
    m_force(force),
    m_angularVelocity(angularVelocity),
    m_torque(torque),
    m_restitution(restitution)
{
    updateDerivedValues();
}

void RigidBody::updateDerivedValues() {
    m_invMass = (m_mass > 0.0f) ? 1.0f / m_mass : 0.0f;
    
    m_invInertia.x = (m_inertia.x > 0.0f) ? 1.0f / m_inertia.x : 0.0f;
    m_invInertia.y = (m_inertia.y > 0.0f) ? 1.0f / m_inertia.y : 0.0f;
    m_invInertia.z = (m_inertia.z > 0.0f) ? 1.0f / m_inertia.z : 0.0f;
}

// Type management
RigidBody::Type RigidBody::getType() const {
    return m_type;
}

void RigidBody::setType(Type type) {
    m_type = type;
}

// Mass properties
float RigidBody::getMass() const {
    return m_mass;
}

void RigidBody::setMass(float mass) {
    m_mass = mass;
    updateDerivedValues();
}

float RigidBody::getInvMass() const {
    return m_invMass;
}

// Inertia properties
const glm::vec3& RigidBody::getInertia() const {
    return m_inertia;
}

void RigidBody::setInertia(const glm::vec3& inertia) {
    m_inertia = inertia;
    updateDerivedValues();
}

const glm::vec3& RigidBody::getInvInertia() const {
    return m_invInertia;
}

// Material properties
float RigidBody::getRestitution() const {
    return m_restitution;
}

void RigidBody::setRestitution(float restitution) {
    m_restitution = restitution;
}

// Linear motion
const glm::vec3& RigidBody::getVelocity() const {
    return m_velocity;
}

void RigidBody::setVelocity(const glm::vec3& velocity) {
    m_velocity = velocity;
}

const glm::vec3& RigidBody::getForce() const {
    return m_force;
}

void RigidBody::applyForce(const glm::vec3& force) {
    m_force += force;
}

void RigidBody::clearForces() {
    m_force = glm::vec3(0.0f);
}

// Angular motion
const glm::vec3& RigidBody::getAngularVelocity() const {
    return m_angularVelocity;
}

void RigidBody::setAngularVelocity(const glm::vec3& angularVelocity) {
    m_angularVelocity = angularVelocity;
}

const glm::vec3& RigidBody::getTorque() const {
    return m_torque;
}

void RigidBody::applyTorque(const glm::vec3& torque) {
    m_torque += torque;
}

void RigidBody::clearTorques() {
    m_torque = glm::vec3(0.0f);
}

// Reset all accumulators
void RigidBody::clearAccumulators() {
    clearForces();
    clearTorques();
}

std::unique_ptr<ecs::components::Component> RigidBody::clone() const {
    return std::make_unique<RigidBody>(*this);
}

}