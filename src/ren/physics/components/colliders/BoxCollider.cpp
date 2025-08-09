#include "physics/components/colliders/BoxCollider.hpp"
using ren::ecs::components::Component;
using ren::physics::components::colliders::BoxCollider;
using ren::physics::components::colliders::geometry::Box;

BoxCollider::BoxCollider()
{
    this->type = Type::Box;
    this->geometry = Box();
}

BoxCollider::BoxCollider(const Box& geometry)
{
    this->type = Type::Box;
    this->geometry = geometry;
}

std::unique_ptr<Component> BoxCollider::clone() const
{
    return std::make_unique<BoxCollider>(*this);
}

const Box& BoxCollider::getGeometry() const
{
    return this->geometry;
}

void BoxCollider::setGeometry(const Box& geometry)
{
    this->geometry = geometry;
}