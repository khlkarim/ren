#include "physics/components/colliders/SphereCollider.hpp"

namespace ren::physics::components::colliders {

SphereCollider::SphereCollider()
    : m_geometry{}
{
    m_type = Type::Sphere;
}

SphereCollider::SphereCollider(const geometry::Sphere& geometry)
    : m_geometry{geometry}
{
    m_type = Type::Sphere;
}

std::unique_ptr<ecs::components::Component> SphereCollider::clone() const
{
    return std::make_unique<SphereCollider>(*this);
}

const geometry::Sphere& SphereCollider::getGeometry() const
{
    return m_geometry;
}

void SphereCollider::setGeometry(const geometry::Sphere& geometry)
{
    m_geometry = geometry;
}

}