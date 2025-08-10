#include "renderer/Camera.hpp"

namespace ren::renderer {

Camera::Camera(
    const glm::vec3& position,
    const glm::vec3& up,
    float yaw,
    float pitch,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    ProjectionType projectionType
)
    : m_position(position),
      m_worldUp(up),
      m_yaw(yaw),
      m_pitch(pitch),
      m_fov(fov),
      m_aspectRatio(aspectRatio),
      m_nearPlane(nearPlane),
      m_farPlane(farPlane),
      m_projectionType(projectionType),
      m_front(0.0f, 0.0f, -1.0f)
{
    updateCameraVectors();
}

// Position and orientation setters
void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
}

void Camera::setUp(const glm::vec3& up) {
    m_worldUp = up;
    updateCameraVectors();
}

void Camera::setYaw(float yaw) {
    m_yaw = yaw;
    updateCameraVectors();
}

void Camera::setPitch(float pitch) {
    m_pitch = glm::clamp(pitch, -89.0f, 89.0f);
    updateCameraVectors();
}

// Projection parameters setters
void Camera::setFov(float fov) {
    m_fov = glm::clamp(fov, 1.0f, 90.0f);
}

void Camera::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
}

void Camera::setNearPlane(float nearPlane) {
    m_nearPlane = nearPlane;
}

void Camera::setFarPlane(float farPlane) {
    m_farPlane = farPlane;
}

void Camera::setProjectionType(ProjectionType type) {
    m_projectionType = type;
}

// Position and orientation getters
const glm::vec3& Camera::getPosition() const { return m_position; }
const glm::vec3& Camera::getFront() const { return m_front; }
const glm::vec3& Camera::getUp() const { return m_up; }
const glm::vec3& Camera::getRight() const { return m_right; }
const glm::vec3& Camera::getWorldUp() const { return m_worldUp; }
float Camera::getYaw() const { return m_yaw; }
float Camera::getPitch() const { return m_pitch; }

// Projection parameters getters
float Camera::getFov() const { return m_fov; }
float Camera::getAspectRatio() const { return m_aspectRatio; }
float Camera::getNearPlane() const { return m_nearPlane; }
float Camera::getFarPlane() const { return m_farPlane; }
Camera::ProjectionType Camera::getProjectionType() const { return m_projectionType; }

// Matrix calculations
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    if (m_projectionType == ProjectionType::Perspective) {
        return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
    } else {
        float orthoHeight = 1.0f;
        float orthoWidth = orthoHeight * m_aspectRatio;
        return glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, m_nearPlane, m_farPlane);
    }
}

void Camera::updateCameraVectors() {
    // Calculate the new front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    newFront.y = sin(glm::radians(m_pitch));
    newFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(newFront);

    // Recalculate the right and up vectors
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

} 