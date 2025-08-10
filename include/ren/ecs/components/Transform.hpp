#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "ecs/components/Component.hpp"

namespace ren::ecs::components 
{

class Transform : public Component
{
public:
    Transform(
        const glm::vec3& position = glm::vec3(0.0f),
        const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 
        const glm::vec3& scale = glm::vec3(1.0f)
    );

    void translate(const glm::vec3& delta);
    void rotate(const glm::quat& delta);
    void rotate(float angleRadians, const glm::vec3& axis);
    void scale(const glm::vec3& factor);

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::quat& rotation);
    void setScale(const glm::vec3& scale);

    const glm::vec3& getPosition() const;
    const glm::quat& getRotation() const;
    const glm::vec3& getScale() const;

    glm::mat4 getModelMatrix() const;
    glm::mat4 getRotationMatrix() const;

    std::unique_ptr<Component> clone() const override;

private:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
};

}