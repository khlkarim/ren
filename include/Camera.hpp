#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ren {

class Camera
{
public:
    enum class ProjectionType {
        Perspective,
        Orthographic
    };

    Camera(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 6.0f),
        const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
        float fov = 45.0f,
        float aspectRatio = 16.0f / 9.0f,
        float nearPlane = 0.1f,
        float farPlane = 100.0f,
        ProjectionType projectionType = ProjectionType::Perspective
    );

    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setUp(const glm::vec3& up);
    void setFOV(float fov);
    void setAspectRatio(float aspectRatio);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    void setProjectionType(ProjectionType type);

    const glm::vec3& getPosition() const;
    const glm::vec3& getTarget() const;
    const glm::vec3& getUp() const;
    float getFOV() const;
    float getAspectRatio() const;
    float getNearPlane() const;
    float getFarPlane() const;
    ProjectionType getProjectionType() const;

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    ProjectionType projectionType;
};

}