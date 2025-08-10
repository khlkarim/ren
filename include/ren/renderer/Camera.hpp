#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ren::renderer {

class Camera {
public:
    enum class ProjectionType {
        Perspective,
        Orthographic
    };

    Camera(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 6.0f), 
        const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), 
        float yaw = -90.0f, 
        float pitch = 0.0f,
        float fov = 45.0f,
        float aspectRatio = 16.0f / 9.0f,
        float nearPlane = 0.1f,
        float farPlane = 100.0f,
        ProjectionType projectionType = ProjectionType::Perspective
    );

    void setPosition(const glm::vec3& position);
    void setUp(const glm::vec3& up);
    void setYaw(float yaw);
    void setPitch(float pitch);

    void setFov(float fov);
    void setAspectRatio(float aspectRatio);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    void setProjectionType(ProjectionType type);

    const glm::vec3& getPosition() const;
    const glm::vec3& getFront() const;
    const glm::vec3& getUp() const;
    const glm::vec3& getRight() const;
    const glm::vec3& getWorldUp() const;
    float getYaw() const;
    float getPitch() const;

    float getFov() const;
    float getAspectRatio() const;
    float getNearPlane() const;
    float getFarPlane() const;
    ProjectionType getProjectionType() const;

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    void updateCameraVectors();

    // Camera position and orientation
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    float m_yaw;
    float m_pitch;

    // Projection parameters
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    ProjectionType m_projectionType;
};

} 