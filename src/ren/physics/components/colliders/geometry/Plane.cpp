#include "physics/components/colliders/geometry/Plane.hpp"
using ren::physics::components::colliders::geometry::Plane;

Plane::Plane(const glm::vec3& normal, float distance)
    : m_normal(normal), m_distance(distance) {}

const glm::vec3& Plane::getNormal() const {
    return m_normal;
}

void Plane::setNormal(const glm::vec3& normal) {
    m_normal = normal;
}

float Plane::getDistance() const {
    return m_distance;
}

void Plane::setDistance(float distance) {
    m_distance = distance;
}