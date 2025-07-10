#ifndef TRANSFORM_HPP 
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
    void translate(glm::vec3 translation);
    void rotate(glm::vec3 rotation);
    void rotate(float degrees, glm::vec3 axis);
    void scale(glm::vec3 scaling);

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

private:
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif // TRANSFORM_HPP