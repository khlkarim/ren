#include "physics/components/colliders/BoxCollider.hpp"

namespace ren::physics::components::colliders {

BoxCollider::BoxCollider()
    : m_geometry{}
{
    m_type = Type::Box;
}

BoxCollider::BoxCollider(const geometry::Box& geometry)
    : m_geometry{geometry}
{
    m_type = Type::Box;
}

std::unique_ptr<ecs::components::Component> BoxCollider::clone() const
{
    return std::make_unique<BoxCollider>(*this);
}

const geometry::Box& BoxCollider::getGeometry() const
{
    return m_geometry;
}

void BoxCollider::setGeometry(const geometry::Box& geometry)
{
    m_geometry = geometry;
}

}