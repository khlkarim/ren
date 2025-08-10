#include "physics/components/Collider.hpp"

namespace ren::physics::components {

bool Collider::getIsTrigger() const {
    return m_isTrigger;
}

void Collider::setIsTrigger(bool isTrigger) {
    m_isTrigger = isTrigger;
}

Collider::Type Collider::getType() const {
    return m_type;
}

} 