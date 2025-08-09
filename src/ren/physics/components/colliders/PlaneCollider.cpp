#include "physics/components/colliders/PlaneCollider.hpp"
using ren::ecs::components::Component;
using ren::physics::components::colliders::PlaneCollider;
using ren::physics::components::colliders::geometry::Plane;

PlaneCollider::PlaneCollider()
{
    this->type = Type::Plane;
    this->geometry = Plane();
}

PlaneCollider::PlaneCollider(const Plane& geometry)
{
    this->type = Type::Plane;
    this->geometry = geometry;
}

std::unique_ptr<Component> PlaneCollider::clone() const
{
    return std::make_unique<PlaneCollider>(*this);
}

const Plane& PlaneCollider::getGeometry() const
{
    return this->geometry;
}

void PlaneCollider::setGeometry(const Plane& geometry)
{
    this->geometry = geometry;
}