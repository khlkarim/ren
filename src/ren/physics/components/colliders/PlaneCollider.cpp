#include "physics/components/colliders/PlaneCollider.hpp"

namespace ren::physics::components::colliders {

PlaneCollider::PlaneCollider()
    : m_geometry{}
{
    m_type = Type::Plane;
}

PlaneCollider::PlaneCollider(const geometry::Plane& geometry)
    : m_geometry{geometry}
{
    m_type = Type::Plane;
}

std::unique_ptr<ecs::components::Component> PlaneCollider::clone() const
{
    return std::make_unique<PlaneCollider>(*this);
}

const geometry::Plane& PlaneCollider::getGeometry() const
{
    return m_geometry;
}

void PlaneCollider::setGeometry(const geometry::Plane& geometry)
{
    m_geometry = geometry;
}

}