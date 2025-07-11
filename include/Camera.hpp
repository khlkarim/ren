#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.hpp"

class Camera 
{
public:
    Camera(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 6.0f), 
        const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f)
    );
    void lookAt(const glm::vec3& target);
    void zoom(float scale);
    glm::mat4 getProjection();

public:
    Transform transform;
};

#endif // CAMERA_HPP