#include "Camera.hpp"
using ren::Camera;

Camera::Camera(
    const glm::vec3& position,
    const glm::vec3& target,
    const glm::vec3& up,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    ProjectionType projectionType
)
{
    this->position = position;
    this->target = target;
    this->up = up;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->projectionType = projectionType;
}

void Camera::setPosition(const glm::vec3& position) {
    this->position = position;
}

void Camera::setTarget(const glm::vec3& target) {
    this->target = target;
}

void Camera::setUp(const glm::vec3& up) {
    this->up = up;
}

void Camera::setFOV(float fov) {
    this->fov = fov;
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

void Camera::setNearPlane(float nearPlane) {
    this->nearPlane = nearPlane;
}

void Camera::setFarPlane(float farPlane) {
    this->farPlane = farPlane;
}

void Camera::setProjectionType(ProjectionType type) {
    this->projectionType = type;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}

const glm::vec3& Camera::getTarget() const {
    return target;
}

const glm::vec3& Camera::getUp() const {
    return up;
}

float Camera::getFOV() const {
    return fov;
}

float Camera::getAspectRatio() const {
    return aspectRatio;
}

float Camera::getNearPlane() const {
    return nearPlane;
}

float Camera::getFarPlane() const {
    return farPlane;
}

Camera::ProjectionType Camera::getProjectionType() const {
    return projectionType;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    if (projectionType == ProjectionType::Perspective) {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    } else {
        float orthoHeight = tan(glm::radians(fov) / 2.0f) * nearPlane;
        float orthoWidth = orthoHeight * aspectRatio;
        return glm::ortho(
            -orthoWidth, orthoWidth,
            -orthoHeight, orthoHeight,
            nearPlane, farPlane
        );
    }
}