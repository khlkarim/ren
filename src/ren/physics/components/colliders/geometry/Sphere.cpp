#include "physics/components/colliders/geometry/Sphere.hpp"
using ren::physics::components::colliders::geometry::Sphere;

Sphere::Sphere(float radius)
    : m_radius(radius) {}

float Sphere::getRadius() const {
    return m_radius;
}

void Sphere::setRadius(float radius) {
    m_radius = radius;
}