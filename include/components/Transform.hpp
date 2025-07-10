#ifndef TRANSFORM_HPP 
#define TRANSFORM_HPP

#include <glm/vec3.hpp>

class Transform 
{
public:
    void translate();
    void rotate();
    void scale();

private:
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif // TRANSFORM_HPP