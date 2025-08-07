#pragma once 

#include <glm/glm.hpp>
#include "ecs/components/Component.hpp"

namespace ren::physics::components
{

class RigidBody : public ecs::components::Component
{
public:
    enum class Type
    {
        Static,
        Dynamic,
        Kinematic
    };

    RigidBody(
        Type type = Type::Dynamic, 
        float mass = 1.0f, 
        const glm::vec3& inertia = glm::vec3(1.0f),
        const glm::vec3& velocity = glm::vec3(0.0f),
        const glm::vec3& force = glm::vec3(0.0f),
        const glm::vec3& angularVelocity = glm::vec3(0.0f),
        const glm::vec3& torque = glm::vec3(0.0f)
    );

    Type getType() const;
    void setType(Type type);

    float getMass() const;
    void setMass(float mass);

    const glm::vec3& getInertia() const;
    void setInertia(const glm::vec3& inertia);

    const glm::vec3& getVelocity() const;
    void setVelocity(const glm::vec3& vel);

    void clearForces();
    const glm::vec3& getForce() const;
    void applyForce(const glm::vec3& force);

    const glm::vec3& getAngularVelocity() const;
    void setAngularVelocity(const glm::vec3& angVel);

    void clearTorques();
    const glm::vec3& getTorque() const;
    void applyTorque(const glm::vec3& torque);

    virtual std::unique_ptr<Component> clone() const;

private:
    Type type;
    float mass;
    glm::vec3 inertia;

    glm::vec3 velocity;
    glm::vec3 force;

    glm::vec3 angularVelocity;
    glm::vec3 torque;
};

}