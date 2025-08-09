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

    // Constructor with default values
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

    // Type management
    Type getType() const;
    void setType(Type type);

    // Mass properties
    float getMass() const;
    void setMass(float mass);
    float getInvMass() const;

    // Inertia properties
    const glm::vec3& getInertia() const;
    void setInertia(const glm::vec3& inertia);
    const glm::vec3& getInvInertia() const;

    // Material properties
    float getRestitution() const;
    void setRestitution(float restitution);

    // Linear motion
    const glm::vec3& getVelocity() const;
    void setVelocity(const glm::vec3& vel);
    const glm::vec3& getForce() const;
    void applyForce(const glm::vec3& force);
    void clearForces();

    // Angular motion
    const glm::vec3& getAngularVelocity() const;
    void setAngularVelocity(const glm::vec3& angVel);
    const glm::vec3& getTorque() const;
    void applyTorque(const glm::vec3& torque);
    void clearTorques();

    // Reset all accumulated forces and torques
    void clearAccumulators();

    // Required by Component base class
    virtual std::unique_ptr<Component> clone() const override;

private:
    // Body properties
    Type type;
    float mass;
    float invMass;
    glm::vec3 inertia;
    glm::vec3 invInertia;

    // Material properties
    float restitution; // Coefficient of restitution (bounciness)

    // Linear motion state
    glm::vec3 velocity;
    glm::vec3 force;

    // Angular motion state
    glm::vec3 angularVelocity;
    glm::vec3 torque;
    
    // Recalculate derived values when mass or inertia changes
    void updateDerivedValues();
};

} // namespace ren::physics::components