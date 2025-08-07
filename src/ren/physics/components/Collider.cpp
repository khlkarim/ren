#include "physics/components/Collider.hpp"
using ren::ecs::components::Component;
using ren::physics::components::Collider;

const bool Collider::getIsTrigger() const {
    return isTrigger;
}

void Collider::setIsTrigger(bool isTrigger) {
    this->isTrigger = isTrigger;
}