#pragma once

#include "physics/components/Collider.hpp"
#include "ecs/components/meshes/Sphere.hpp"

namespace ren::physics::components::colliders
{

class SphereCollider : public Collider
{
public:
    SphereCollider() = default;
    SphereCollider(const ecs::components::meshes::Sphere& geometry);

    Type getType() const;

    const ecs::components::meshes::Sphere& getGeometry() const;
    void setGeometry(const ecs::components::meshes::Sphere& geom);

    std::unique_ptr<ecs::components::Component> clone() const;

private:
    Type type;
    ecs::components::meshes::Sphere geometry;
};

}