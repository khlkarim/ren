#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.hpp"

class Camera 
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 target = glm::vec3(0.0f));
    void lookAt(glm::vec3 target);

public:
    Transform transform;
};

#endif // CAMERA_HPP