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
        const glm::vec3& torque = glm::vec3(0.0f),
        float restitution = 0.5f
    );

    Type getType() const;
    void setType(Type type);

    float getMass() const;
    void setMass(float mass);
    float getInvMass() const;

    const glm::vec3& getInertia() const;
    void setInertia(const glm::vec3& inertia);
    const glm::vec3& getInvInertia() const;

    float getRestitution() const;
    void setRestitution(float restitution);

    const glm::vec3& getVelocity() const;
    void setVelocity(const glm::vec3& vel);
    const glm::vec3& getForce() const;
    void applyForce(const glm::vec3& force);
    void clearForces();

    const glm::vec3& getAngularVelocity() const;
    void setAngularVelocity(const glm::vec3& angVel);
    const glm::vec3& getTorque() const;
    void applyTorque(const glm::vec3& torque);
    void clearTorques();

    // Reset all accumulated forces and torques
    void clearAccumulators();

    virtual std::unique_ptr<Component> clone() const override;

private:
    // Body properties
    Type m_type;
    float m_mass;
    float m_invMass;
    glm::vec3 m_inertia;
    glm::vec3 m_invInertia;

    // Material properties
    float m_restitution; // Coefficient of restitution (bounciness)

    // Linear motion state
    glm::vec3 m_velocity;
    glm::vec3 m_force;

    // Angular motion state
    glm::vec3 m_angularVelocity;
    glm::vec3 m_torque;
    // Recalculate derived values when mass or inertia changes
    void updateDerivedValues();
};

}