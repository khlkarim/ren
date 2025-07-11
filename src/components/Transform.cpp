#include "Transform.hpp"

void Transform::translate(glm::vec3 translation)
{
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, translation);

    this->_position = trans * glm::vec4(this->_position, 1.0f);
}

void Transform::rotate(glm::vec3 rotation)
{
    glm::quat rotQuat = glm::quat(glm::radians(rotation));
    glm::quat currQuat = glm::quat(glm::radians(this->_rotation));

    this->_rotation = glm::degrees(glm::eulerAngles(rotQuat * currQuat));
}

void Transform::rotate(float degrees, glm::vec3 axis)
{
    glm::quat rotQuat = glm::angleAxis(glm::radians(degrees), glm::normalize(axis));
    glm::quat currQuat = glm::quat(glm::radians(this->_rotation));

    this->_rotation = glm::degrees(glm::eulerAngles(rotQuat * currQuat));
}

void Transform::scale(glm::vec3 scaling)
{
    glm::mat4 trans(1.0f);
    trans = glm::scale(trans, scaling);

    this->_scale = trans * glm::vec4(this->_scale, 1.0f);
}

void Transform::setPosition(const glm::vec3& position)
{
    this->_position = position;
}

void Transform::setRotation(const glm::vec3& rotation)
{
    this->_rotation = rotation;
}

void Transform::setScale(const glm::vec3& scale)
{
    this->_scale = scale;
}

glm::vec3 Transform::getPosition() const
{
    return this->_position;
}

glm::vec3 Transform::getRotation() const
{
    return this->_rotation;
}

glm::vec3 Transform::getScale() const
{
    return this->_scale;
}

glm::mat4 Transform::getModel() const
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, this->_position);
    glm::quat rotationQuat = glm::quat(glm::radians(this->_rotation));
    model *= glm::mat4_cast(rotationQuat);
    model = glm::scale(model, this->_scale);

    return model;
}

glm::mat4 Transform::getView() const
{
    return glm::inverse(this->getModel());
}