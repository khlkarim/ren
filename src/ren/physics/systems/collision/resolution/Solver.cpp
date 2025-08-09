#include <spdlog/spdlog.h>
#include "ecs/components/Transform.hpp"
#include "physics/components/RigidBody.hpp"
#include "physics/systems/collision/ManifoldPoints.hpp"
#include "physics/systems/collision/resolution/Solver.hpp"

namespace ren::physics::systems::collision::resolution {

void Solver::solve(
    const float dt,
    components::RigidBody& r1,
    components::RigidBody& r2,
    ManifoldPoints& manifoldPoints
) {
    // Early exit if no contacts
    if (manifoldPoints.contacts.empty()) {
        return;
    }

    // Early exit if both bodies have infinite mass
    const float invMassSum = r1.getInvMass() + r2.getInvMass();
    if (invMassSum <= 0.0f) {
        return;
    }

    const float restitution = std::min(r1.getRestitution(), r2.getRestitution());
    const float contactScalar = 1.0f / static_cast<float>(manifoldPoints.contacts.size());

    for (const auto& contact : manifoldPoints.contacts) {
        const glm::vec3 relativeVelocity = r2.getVelocity() - r1.getVelocity();
        const float velAlongNormal = glm::dot(relativeVelocity, contact.normal);

        // Skip if objects are separating
        if (velAlongNormal > 0.0f) {
            continue;
        }

        // Calculate impulse scalar
        const float j = -(1.0f + restitution) * velAlongNormal * contactScalar / invMassSum;

        // Apply impulse
        const glm::vec3 impulse = j * contact.normal;
        
        r1.setVelocity(r1.getVelocity() - r1.getInvMass() * impulse);
        r2.setVelocity(r2.getVelocity() + r2.getInvMass() * impulse);
    }
}

} // namespace ren::physics::systems::collision::resolution
