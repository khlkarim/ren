#include "physics/components/RigidBody.hpp"
using ren::ecs::components::Component;
using ren::physics::components::RigidBody;

RigidBody::RigidBody(
    Type type, 
    float mass, 
    const glm::vec3& inertia,
    const glm::vec3& velocity,
    const glm::vec3& force,
    const glm::vec3& angularVelocity,
    const glm::vec3& torque,
    float restitution
) : type(type),
    mass(mass),
    inertia(inertia),
    velocity(velocity),
    force(force),
    angularVelocity(angularVelocity),
    torque(torque),
    restitution(restitution)
{
    updateDerivedValues();
}

void RigidBody::updateDerivedValues() {
    invMass = (mass > 0.0f) ? 1.0f / mass : 0.0f;
    
    // Calculate inverse inertia for each axis
    invInertia.x = (inertia.x > 0.0f) ? 1.0f / inertia.x : 0.0f;
    invInertia.y = (inertia.y > 0.0f) ? 1.0f / inertia.y : 0.0f;
    invInertia.z = (inertia.z > 0.0f) ? 1.0f / inertia.z : 0.0f;
}

// Type management
RigidBody::Type RigidBody::getType() const {
    return type;
}

void RigidBody::setType(Type type) {
    this->type = type;
}

// Mass properties
float RigidBody::getMass() const {
    return mass;
}

void RigidBody::setMass(float mass) {
    this->mass = mass;
    updateDerivedValues();
}

float RigidBody::getInvMass() const {
    return invMass;
}

// Inertia properties
const glm::vec3& RigidBody::getInertia() const {
    return inertia;
}

void RigidBody::setInertia(const glm::vec3& inertia) {
    this->inertia = inertia;
    updateDerivedValues();
}

const glm::vec3& RigidBody::getInvInertia() const {
    return invInertia;
}

// Material properties
float RigidBody::getRestitution() const {
    return restitution;
}

void RigidBody::setRestitution(float restitution) {
    this->restitution = restitution;
}

// Linear motion
const glm::vec3& RigidBody::getVelocity() const {
    return velocity;
}

void RigidBody::setVelocity(const glm::vec3& vel) {
    velocity = vel;
}

const glm::vec3& RigidBody::getForce() const {
    return force;
}

void RigidBody::applyForce(const glm::vec3& force) {
    this->force += force;
}

void RigidBody::clearForces() {
    force = glm::vec3(0.0f);
}

// Angular motion
const glm::vec3& RigidBody::getAngularVelocity() const {
    return angularVelocity;
}

void RigidBody::setAngularVelocity(const glm::vec3& angVel) {
    angularVelocity = angVel;
}

const glm::vec3& RigidBody::getTorque() const {
    return torque;
}

void RigidBody::applyTorque(const glm::vec3& torque) {
    this->torque += torque;
}

void RigidBody::clearTorques() {
    torque = glm::vec3(0.0f);
}

// Reset all accumulators
void RigidBody::clearAccumulators() {
    clearForces();
    clearTorques();
}

// Component interface implementation
std::unique_ptr<Component> RigidBody::clone() const {
    return std::make_unique<RigidBody>(*this);
}