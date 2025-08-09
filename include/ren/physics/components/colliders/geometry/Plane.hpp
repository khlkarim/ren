#pragma once

#include <glm/glm.hpp>

namespace ren::physics::components::colliders::geometry {

class Plane {
public:
    Plane(const glm::vec3& normal = glm::vec3(0.0f, 1.0f, 0.0f), float distance = 1.0f);

    const glm::vec3& getNormal() const;
    void setNormal(const glm::vec3& normal);
    
    float getDistance() const;
    void setDistance(float distance);

private:
    glm::vec3 m_normal; 
    float m_distance;
};

}