#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target)
{
    this->transform.setPosition(position);
    this->lookAt(target);
}

void Camera::lookAt(glm::vec3 target) 
{  
    glm::vec3 direction = glm::normalize(target - this->transform.getPosition());

    float yaw = glm::degrees(atan2(direction.x, direction.z));
    float pitch = glm::degrees(asin(-direction.y));

    this->transform.setRotation(glm::vec3(pitch, yaw, 0.0f));
}