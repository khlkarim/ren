#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target)
{
    this->position = position;
    this->direction = glm::normalize(position - target);
    this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->direction));
    this->up = glm::normalize(glm::cross(this->direction, this->right));

    this->lookAt(target);
}

void Camera::lookAt(glm::vec3 target)
{
    glm::mat4 view;
    view = glm::lookAt(
        this->position, 
  		target, 
  		glm::vec3(0.0f, 1.0f, 0.0f)
    );
}