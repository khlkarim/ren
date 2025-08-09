#include "ecs/components/Transform.hpp"
#include "physics/components/Collider.hpp"
#include "physics/systems/collision/ManifoldPoints.hpp"
#include "physics/systems/collision/detection/narrow.hpp"

namespace ren::physics::systems::collision::detection::narrow {

std::optional<ManifoldPoints> SAT(
    const components::Collider& a,
    const ecs::components::Transform& ta,
    const components::Collider& b,
    const ecs::components::Transform& tb
) {
    return std::nullopt;
}   

std::optional<ManifoldPoints> GTK(  
    const components::Collider&,
    const ecs::components::Transform&,
    const components::Collider&,
    const ecs::components::Transform&
) {
    return std::nullopt;
}

} 