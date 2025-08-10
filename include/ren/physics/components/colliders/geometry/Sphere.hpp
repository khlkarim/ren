#pragma once

namespace ren::physics::components::colliders::geometry {

class Sphere {
public:
    explicit Sphere(float radius = 1.0f);

    float getRadius() const;
    void setRadius(float radius);

private:
    float m_radius;
};

}