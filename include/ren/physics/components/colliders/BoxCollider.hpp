#pragma once

#include "physics/components/Collider.hpp"
#include "physics/components/colliders/geometry/Box.hpp"

namespace ren::physics::components::colliders
{

class BoxCollider : public Collider
{
public:
    BoxCollider();
    explicit BoxCollider(const geometry::Box& geometry);

    const geometry::Box& getGeometry() const;
    void setGeometry(const geometry::Box& geometry);

    std::unique_ptr<ecs::components::Component> clone() const;

private:
    geometry::Box m_geometry;
};

}