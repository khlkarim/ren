#include "ecs/components/Transform.hpp"

namespace ren::ecs::components {

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
    : m_position(position)
    , m_rotation(rotation)
    , m_scale(scale)
{
}

void Transform::translate(const glm::vec3& delta)
{
    m_position += delta;
}

void Transform::rotate(const glm::quat& delta)
{
    m_rotation = glm::normalize(delta * m_rotation);
}

void Transform::rotate(float degrees, const glm::vec3& axis)
{
    const glm::quat delta = glm::angleAxis(glm::radians(degrees), glm::normalize(axis));
    m_rotation = glm::normalize(delta * m_rotation);
}

void Transform::scale(const glm::vec3& factor)
{
    m_scale *= factor;
}

void Transform::setPosition(const glm::vec3& position)
{
    m_position = position;
}

void Transform::setRotation(const glm::quat& rotation)
{
    m_rotation = rotation;
}

void Transform::setScale(const glm::vec3& scale)
{
    m_scale = scale;
}

const glm::vec3& Transform::getPosition() const
{
    return m_position;
}

const glm::quat& Transform::getRotation() const
{
    return m_rotation;
}

const glm::vec3& Transform::getScale() const
{
    return m_scale;
}

glm::mat4 Transform::getModelMatrix() const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_position);
    model *= glm::mat4_cast(m_rotation);
    model = glm::scale(model, m_scale);
    return model;
}

glm::mat4 Transform::getRotationMatrix() const
{
    return glm::mat4_cast(m_rotation);
}

std::unique_ptr<Component> Transform::clone() const
{
    return std::make_unique<Transform>(*this);
}

}