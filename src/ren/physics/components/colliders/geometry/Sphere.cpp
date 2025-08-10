#include "physics/components/colliders/geometry/Sphere.hpp"

namespace ren::physics::components::colliders::geometry {

Sphere::Sphere(float radius)
    : m_radius(radius) {}

float Sphere::getRadius() const {
    return m_radius;
}

void Sphere::setRadius(float radius) {
    m_radius = radius;
}

} 