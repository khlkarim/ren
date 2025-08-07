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
    const glm::vec3& torque
)
{
    this->type = type;
    this->mass = mass;
    this->inertia = inertia;

    this->velocity = velocity;
    this->force = force;
    
    this->angularVelocity = angularVelocity;
    this->torque = torque;
}

RigidBody::Type RigidBody::getType() const {
    return type;
}

void RigidBody::setType(Type type) {
    this->type = type;
}

float RigidBody::getMass() const {
    return mass;
}

void RigidBody::setMass(float mass) {
    this->mass = mass;
}

const glm::vec3& RigidBody::getInertia() const {
    return inertia;
}

void RigidBody::setInertia(const glm::vec3& inertia) {
    this->inertia = inertia;
}

const glm::vec3& RigidBody::getVelocity() const {
    return velocity;
}

void RigidBody::setVelocity(const glm::vec3& vel) {
    velocity = vel;
}

void RigidBody::clearForces() {
    force = glm::vec3(0.0f);
}

const glm::vec3& RigidBody::getForce() const {
    return force;
}

void RigidBody::applyForce(const glm::vec3& force) {
    this->force += force;
}

const glm::vec3& RigidBody::getAngularVelocity() const {
    return angularVelocity;
}

void RigidBody::setAngularVelocity(const glm::vec3& angVel) {
    angularVelocity = angVel;
}

void RigidBody::clearTorques() {
    torque = glm::vec3(0.0f);
}

const glm::vec3& RigidBody::getTorque() const {
    return torque;
}

void RigidBody::applyTorque(const glm::vec3& torque) {
    this->torque += torque;
}

std::unique_ptr<Component> RigidBody::clone() const {
    return std::make_unique<RigidBody>(*this);
}