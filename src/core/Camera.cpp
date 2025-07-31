#include <core/Camera.hpp>
using ren::Camera;

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    ProjectionType projectionType
)
    : position(position),
      worldUp(up),
      yaw(yaw),
      pitch(pitch),
      fov(fov),
      aspectRatio(aspectRatio),
      nearPlane(nearPlane),
      farPlane(farPlane),
      projectionType(projectionType)
{
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    updateCameraVectors();
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Camera::setUp(const glm::vec3& upVec) {
    worldUp = upVec;
    updateCameraVectors();
}

void Camera::setYaw(float y) {
    yaw = y;
    updateCameraVectors();
}

void Camera::setPitch(float p) {
    pitch = glm::clamp(p, -89.0f, 89.0f);
    updateCameraVectors();
}

void Camera::setFOV(float f) {
    fov = glm::clamp(f, 1.0f, 90.0f);
}

void Camera::setAspectRatio(float ratio) {
    aspectRatio = ratio;
}

void Camera::setNearPlane(float nearZ) {
    nearPlane = nearZ;
}

void Camera::setFarPlane(float farZ) {
    farPlane = farZ;
}

void Camera::setProjectionType(ProjectionType type) {
    projectionType = type;
}

const glm::vec3& Camera::getPosition() const { return position; }
const glm::vec3& Camera::getFront() const { return front; }
const glm::vec3& Camera::getUp() const { return up; }
const glm::vec3& Camera::getRight() const { return right; }
const glm::vec3& Camera::getWorldUp() const { return worldUp; }

float Camera::getYaw() const { return yaw; }
float Camera::getPitch() const { return pitch; }

float Camera::getFOV() const { return fov; }
float Camera::getAspectRatio() const { return aspectRatio; }
float Camera::getNearPlane() const { return nearPlane; }
float Camera::getFarPlane() const { return farPlane; }
Camera::ProjectionType Camera::getProjectionType() const { return projectionType; }

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    if (projectionType == ProjectionType::Perspective) {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    } else {
        float orthoHeight = 1.0f;
        float orthoWidth = orthoHeight * aspectRatio;
        return glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearPlane, farPlane);
    }
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}