#include "physics/components/colliders/geometry/Box.hpp"
using ren::physics::components::colliders::geometry::Box;

Box::Box(float width, float height, float depth)
    : m_width(width), m_height(height), m_depth(depth) {}

float Box::getWidth() const {
    return m_width;
}

float Box::getHeight() const {
    return m_height;
}

float Box::getDepth() const {
    return m_depth;
}

void Box::setWidth(float width) {
    m_width = width;
}

void Box::setHeight(float height) {
    m_height = height;
}

void Box::setDepth(float depth) {
    m_depth = depth;
}

glm::vec3 Box::getHalfExtents() const {
    return glm::vec3(m_width * 0.5f, m_height * 0.5f, m_depth * 0.5f);
}

glm::vec3 Box::getMin() const {
    return glm::vec3(-m_width * 0.5f, -m_height * 0.5f, -m_depth * 0.5f);
}

glm::vec3 Box::getMax() const {
    return glm::vec3(m_width * 0.5f, m_height * 0.5f, m_depth * 0.5f);
}