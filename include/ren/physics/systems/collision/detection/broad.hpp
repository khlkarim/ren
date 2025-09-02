#pragma once

#include <optional>
#include <glm/glm.hpp>

namespace ren::ecs::components { class Transform; }
namespace ren::physics::systems::collision { struct ManifoldPoints; }
namespace ren::physics::components::colliders { 
    class BoxCollider; 
    class SphereCollider; 
}

namespace ren::physics::systems::collision::detection::broad {

constexpr float EPSILON = 1e-6f;

ManifoldPoints createSingleContactManifold(
    const glm::vec3& position, 
    const glm::vec3& normal,
    float penetration
);

std::optional<ManifoldPoints> AABB(
    const components::colliders::BoxCollider&,
    const ecs::components::Transform&,
    const components::colliders::BoxCollider&,
    const ecs::components::Transform&
);

std::optional<ManifoldPoints> OBB(
    const components::colliders::BoxCollider&,
    const ecs::components::Transform&,
    const components::colliders::BoxCollider&,
    const ecs::components::Transform&
);

std::optional<ManifoldPoints> BoundingSpheres(
    const components::colliders::SphereCollider&,
    const ecs::components::Transform&,
    const components::colliders::SphereCollider&,
    const ecs::components::Transform&
);

} 