#include "Camera.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& target)
{
    this->transform.setPosition(position);
    this->lookAt(target);
}

void Camera::lookAt(const glm::vec3& target)
{
    glm::vec3 position = glm::normalize(target - this->transform.getPosition());
    glm::vec3 direction = glm::normalize(target - position);
    glm::quat orientation = glm::quatLookAt(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    this->transform.setRotation(glm::eulerAngles(orientation));
}

void Camera::zoom(float scale)
{
    this->transform.setScale(glm::vec3(scale));
}

glm::mat4 Camera::getProjection()
{
    return glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}