#include <components/Transform.hpp>
using ren::components::Component;
using ren::components::Transform;

Transform::Transform()
{
    this->_position = glm::vec3(0.0f);
    this->_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    this->_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
{
    this->_position = position;
    this->_rotation = rotation;
    this->_scale = scale;
}

void Transform::translate(const glm::vec3& delta)
{
    this->_position += delta;
}

void Transform::rotate(const glm::quat& delta)
{
    this->_rotation = glm::normalize(delta * this->_rotation);
}

void Transform::rotate(float degrees, const glm::vec3& axis)
{
    glm::quat delta = glm::angleAxis(glm::radians(degrees), glm::normalize(axis));
    this->_rotation = glm::normalize(delta * this->_rotation);
}

void Transform::scale(const glm::vec3& factor)
{
    this->_scale *= factor;
}

void Transform::setPosition(const glm::vec3& position)
{
    this->_position = position;
}

void Transform::setRotation(const glm::quat& rotation)
{
    this->_rotation = rotation;
}

void Transform::setScale(const glm::vec3& scale)
{
    this->_scale = scale;
}

glm::vec3& Transform::getPosition() 
{
    return this->_position;
}

glm::quat& Transform::getRotation() 
{
    return this->_rotation;
}

glm::vec3& Transform::getScale() 
{
    return this->_scale;
}

glm::mat4 Transform::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->_position);
    model *= glm::mat4_cast(this->_rotation);
    model = glm::scale(model, this->_scale);
    return model;
}

std::unique_ptr<Component> Transform::clone() const {
    return std::make_unique<Transform>(*this);
}