#pragma once

#include <array>
#include <cstddef>
#include <optional>
#include <functional>
#include "physics/components/Collider.hpp"

namespace ren::ecs::components {
    class Transform;
}

namespace ren::physics::systems::collision {
    struct ManifoldPoints;
}

namespace ren::physics::systems::collision::detection {

    constexpr std::size_t ColliderTypeCount = static_cast<std::size_t>(components::Collider::Type::Count);

    using CollisionTestFunc = std::optional<physics::systems::collision::ManifoldPoints>(*)(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );

    std::optional<physics::systems::collision::ManifoldPoints> TestBoxBox(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );
    std::optional<physics::systems::collision::ManifoldPoints> TestPlanePlane(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );
    std::optional<physics::systems::collision::ManifoldPoints> TestSphereSphere(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );
    std::optional<physics::systems::collision::ManifoldPoints> TestBoxPlane(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );
    std::optional<physics::systems::collision::ManifoldPoints> TestSphereBox(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );
    std::optional<physics::systems::collision::ManifoldPoints> TestSpherePlane(
        const physics::components::Collider&,
        const ecs::components::Transform&,
        const physics::components::Collider&,
        const ecs::components::Transform&
    );

    inline const std::array<std::array<CollisionTestFunc, ColliderTypeCount>, ColliderTypeCount> dispatchTable{{
        //        Box                Plane                Sphere
        /* Box   */  { TestBoxBox,           TestBoxPlane,            TestSphereBox },
        /* Plane */  { TestBoxPlane,         TestPlanePlane,          TestSpherePlane },
        /* Sphere*/  { TestSphereBox,        TestSpherePlane,         TestSphereSphere }
    }};

}