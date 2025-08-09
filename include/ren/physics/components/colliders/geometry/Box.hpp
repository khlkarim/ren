#pragma once

#include <glm/glm.hpp>

namespace ren::physics::components::colliders::geometry 
{

class Box {
public:
    Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

    float getWidth() const;
    float getHeight() const;
    float getDepth() const;

    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);

    glm::vec3 getHalfExtents() const;

    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

private:
    float m_width;
    float m_height;
    float m_depth;
};

}