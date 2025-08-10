#pragma once

#include "physics/components/Collider.hpp"
#include "physics/components/colliders/geometry/Plane.hpp"

namespace ren::physics::components::colliders
{

class PlaneCollider : public Collider
{
public:
    PlaneCollider();
    explicit PlaneCollider(const geometry::Plane& geometry);

    const geometry::Plane& getGeometry() const;
    void setGeometry(const geometry::Plane& geometry);

    std::unique_ptr<ecs::components::Component> clone() const;

private:
    geometry::Plane m_geometry;
};

}