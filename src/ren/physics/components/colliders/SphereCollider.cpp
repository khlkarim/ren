#include "physics/components/colliders/SphereCollider.hpp"
using ren::ecs::components::Component;
using ren::ecs::components::meshes::Sphere;
using ren::physics::components::colliders::SphereCollider;

SphereCollider::SphereCollider(const Sphere& geometry)
{
    this->type = Type::Sphere;
    this->geometry = geometry;
}

std::unique_ptr<Component> SphereCollider::clone() const
{
    return std::make_unique<SphereCollider>(*this);
}

const Sphere& SphereCollider::getGeometry() const
{
    return this->geometry;
}

void SphereCollider::setGeometry(const Sphere& geometry)
{
    this->geometry = geometry;
}