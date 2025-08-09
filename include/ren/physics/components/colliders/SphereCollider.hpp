#pragma once

#include "physics/components/Collider.hpp"
#include "physics/components/colliders/geometry/Sphere.hpp"

namespace ren::physics::components::colliders
{

class SphereCollider : public Collider
{
public:
    SphereCollider();
    SphereCollider(const geometry::Sphere& geometry);

    const geometry::Sphere& getGeometry() const;
    void setGeometry(const geometry::Sphere& geometry);

    std::unique_ptr<ecs::components::Component> clone() const;

private:
    geometry::Sphere geometry;
};

}