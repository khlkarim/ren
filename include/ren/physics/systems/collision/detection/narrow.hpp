#pragma once

#include <optional>

namespace ren::ecs::components { class Transform; }
namespace ren::physics::components { class Collider; }
namespace ren::physics::systems::collision { struct ManifoldPoints; }

namespace ren::physics::systems::collision::detection::narrow {

std::optional<ManifoldPoints> SAT(
    const components::Collider&,
    const ecs::components::Transform&,
    const components::Collider&,
    const ecs::components::Transform&
);

std::optional<ManifoldPoints> GTK(
    const components::Collider&,
    const ecs::components::Transform&,
    const components::Collider&,
    const ecs::components::Transform&
);

} 