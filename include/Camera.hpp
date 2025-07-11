#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera 
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f));
    void lookAt(glm::vec3 target);

public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
};

#endif // CAMERA_HPP