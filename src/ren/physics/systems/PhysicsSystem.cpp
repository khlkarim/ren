#include <vector>
#include <string>

#include "ecs/entities/EntityManager.hpp"
#include "ecs/components/Transform.hpp"
#include "physics/components/Collider.hpp"
#include "physics/components/RigidBody.hpp"
#include "physics/systems/dynamics/Solver.hpp"
#include "physics/systems/collision/ManifoldPoints.hpp"
#include "physics/systems/collision/resolution/Solver.hpp"
#include "physics/systems/collision/detection/dispatchTable.hpp"
#include "physics/systems/PhysicsSystem.hpp"

namespace ren::physics::systems {

void PhysicsSystem::update(float dt, ecs::entities::EntityManager& entityManager)
{
    updateDynamics(dt, entityManager);
    handleCollisions(dt, entityManager);
}

void PhysicsSystem::handleCollisions(float dt, ecs::entities::EntityManager& entityManager)
{
    collision::resolution::Solver collisionSolver;
    std::vector<std::string> entitiesWithCollider = entityManager.getEntitiesWith<components::Collider>();

    for(size_t i = 0; i < entitiesWithCollider.size(); i++)
    {
        for(size_t j = i + 1; j < entitiesWithCollider.size(); j++)
        {
            auto& e1 = entityManager.get(entitiesWithCollider[i]).value().get();
            auto& e2 = entityManager.get(entitiesWithCollider[j]).value().get();

            auto& cm1 = e1.getComponentManager();
            auto& cm2 = e2.getComponentManager();

            using ecs::components::Transform;
            using components::Collider;
            using components::RigidBody;

            if (!cm1.has<Transform, Collider>() || !cm2.has<Transform, Collider>()) {
                continue;
            }

            auto& c1 = cm1.get<Collider>().value().get();
            auto& c2 = cm2.get<Collider>().value().get();
            auto& t1 = cm1.get<Transform>().value().get();
            auto& t2 = cm2.get<Transform>().value().get();

            auto& manifoldPointsOpt = collision::detection::dispatchTable
                [static_cast<int>(c1.getType())]
                [static_cast<int>(c2.getType())]
                (c1, t1, c2, t2);

            if(manifoldPointsOpt && cm1.has<RigidBody>() && cm2.has<RigidBody>())
            {
                auto& r1 = cm1.get<RigidBody>().value().get();
                auto& r2 = cm2.get<RigidBody>().value().get();

                collisionSolver.solve(dt, r1, r2, manifoldPointsOpt.value());
            }
        }
    }
}

void PhysicsSystem::updateDynamics(float dt, ecs::entities::EntityManager& entityManager)
{
    dynamics::Solver dynamicsSolver;
    std::vector<std::string> entitiesWithRigidbody = 
        entityManager.getEntitiesWith<components::RigidBody>();

    for(const auto& entityId : entitiesWithRigidbody)
    {
        auto transformOpt = entityManager.getComponent<ecs::components::Transform>(entityId);
        auto rigidBodyOpt = entityManager.getComponent<components::RigidBody>(entityId);
        
        if (transformOpt && rigidBodyOpt) {
            auto& transform = transformOpt.value().get();
            auto& rigidBody = rigidBodyOpt.value().get();
            
            dynamicsSolver.solve(dt, rigidBody, transform);
        }
    }
}

std::unique_ptr<ecs::systems::System> PhysicsSystem::clone() const
{
    return std::make_unique<PhysicsSystem>(*this);
}

}