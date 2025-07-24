#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <components/Component.hpp>

namespace ren::components {

class Transform : public Component
{
public:
    Transform();
    Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

    void translate(const glm::vec3& delta);
    void rotate(const glm::quat& delta);
    void rotate(float angleRadians, const glm::vec3& axis);
    void scale(const glm::vec3& factor);

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::quat& rotation);
    void setScale(const glm::vec3& scale);

    glm::vec3& getPosition();
    glm::quat& getRotation();
    glm::vec3& getScale();

    glm::mat4 getModelMatrix() const;

    std::unique_ptr<Component> clone() const override;

private:
    glm::vec3 _position;
    glm::quat _rotation;
    glm::vec3 _scale;
};

}