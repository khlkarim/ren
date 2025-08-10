#include <spdlog/spdlog.h>
#include "ecs/components/Transform.hpp"
#include "physics/components/Collider.hpp"
#include "physics/components/colliders/BoxCollider.hpp"
#include "physics/components/colliders/PlaneCollider.hpp"
#include "physics/components/colliders/SphereCollider.hpp"
#include "physics/systems/collision/ManifoldPoints.hpp"
#include "physics/systems/collision/detection/broad.hpp"
#include "physics/systems/collision/detection/narrow.hpp"
#include "physics/systems/collision/detection/dispatchTable.hpp"

namespace ren::physics::systems::collision::detection {

std::optional<ManifoldPoints> TestBoxBox(
        const components::Collider& c1, const ecs::components::Transform& t1,
        const components::Collider& c2, const ecs::components::Transform& t2) {
    
    auto* bc1 = dynamic_cast<const components::colliders::BoxCollider*>(&c1);
    auto* bc2 = dynamic_cast<const components::colliders::BoxCollider*>(&c2);

    if (!bc1 || !bc2) {
        LogWrongCollisionTest("TestBoxBox", c1, c2);
        return std::nullopt;
    }

    // Check if rotations are identity (no rotation)
    const float epsilon = 1e-5f;
    glm::quat rot1 = t1.getRotation();
    glm::quat rot2 = t2.getRotation();
    
    // Identity quaternion is (w=1, x=0, y=0, z=0)
    bool isIdentity1 = std::abs(rot1.w - 1.0f) < epsilon && 
                       std::abs(rot1.x) < epsilon && 
                       std::abs(rot1.y) < epsilon && 
                       std::abs(rot1.z) < epsilon;
                       
    bool isIdentity2 = std::abs(rot2.w - 1.0f) < epsilon && 
                       std::abs(rot2.x) < epsilon && 
                       std::abs(rot2.y) < epsilon && 
                       std::abs(rot2.z) < epsilon;

    if (isIdentity1 && isIdentity2) {
        return broad::AABB(*bc1, t1, *bc2, t2);
    } else {
        return broad::OBB(*bc1, t1, *bc2, t2);
    }
}

std::optional<ManifoldPoints> TestPlanePlane(
        const components::Collider& c1, const ecs::components::Transform& t1,
        const components::Collider& c2, const ecs::components::Transform& t2) {
    
    auto* pc1 = dynamic_cast<const components::colliders::PlaneCollider*>(&c1);
    auto* pc2 = dynamic_cast<const components::colliders::PlaneCollider*>(&c2);

    if (!pc1 || !pc2) {
        LogWrongCollisionTest("TestPlanePlane", c1, c2);
        return std::nullopt;
    }

    constexpr float kParallelThreshold = 0.999f;
    constexpr float kDistanceThreshold = 1e-4f;

    // Two planes collide if they are coincident (normals parallel and distance equal)
    glm::vec3 n1 = t1.getRotation() * pc1->getGeometry().getNormal();
    glm::vec3 n2 = t2.getRotation() * pc2->getGeometry().getNormal();
    float d1 = glm::dot(n1, t1.getPosition());
    float d2 = glm::dot(n2, t2.getPosition());

    if (glm::abs(glm::dot(n1, n2)) > kParallelThreshold && 
        glm::abs(d1 - d2) < kDistanceThreshold) {
        
        ManifoldPoints manifold;
        Contact contact;
        contact.position = t1.getPosition(); 
        contact.normal = n1;
        contact.penetration = 0.0f;
        manifold.contacts.push_back(contact);

        return manifold;
    }
    return std::nullopt;
}

std::optional<ManifoldPoints> TestSphereSphere(
        const components::Collider& c1, const ecs::components::Transform& t1,
        const components::Collider& c2, const ecs::components::Transform& t2) {
    
    auto* sc1 = dynamic_cast<const components::colliders::SphereCollider*>(&c1);
    auto* sc2 = dynamic_cast<const components::colliders::SphereCollider*>(&c2);

    if (!sc1 || !sc2) {
        LogWrongCollisionTest("TestSphereSphere", c1, c2);
        return std::nullopt;
    }

    return broad::BoundingSpheres(*sc1, t1, *sc2, t2);
}

std::optional<ManifoldPoints> TestBoxPlane(
        const components::Collider& c1, const ecs::components::Transform& t1,
        const components::Collider& c2, const ecs::components::Transform& t2) {
    
    auto* bc = dynamic_cast<const components::colliders::BoxCollider*>(&c1);
    auto* pc = dynamic_cast<const components::colliders::PlaneCollider*>(&c2);

    if (!bc || !pc) {
        LogWrongCollisionTest("TestBoxPlane", c1, c2);
        return std::nullopt;
    }

    // Get box corners in world space
    glm::vec3 boxMin = bc->getGeometry().getMin();
    glm::vec3 boxMax = bc->getGeometry().getMax();
    glm::mat4 boxTransform = t1.getModelMatrix();
    glm::vec3 planeNormal = t2.getRotation() * pc->getGeometry().getNormal();
    float planeD = -glm::dot(planeNormal, t2.getPosition());

    ManifoldPoints manifold;
    float minPenetration = std::numeric_limits<float>::max();
    glm::vec3 contactPoint;
    bool collided = false;

    // 8 corners of the box
    for (int i = 0; i < 8; ++i) {
        glm::vec3 corner{
            (i & 1) ? boxMax.x : boxMin.x,
            (i & 2) ? boxMax.y : boxMin.y,
            (i & 4) ? boxMax.z : boxMin.z
        };
        glm::vec3 worldCorner = glm::vec3(boxTransform * glm::vec4(corner, 1.0f));
        float dist = glm::dot(planeNormal, worldCorner) + planeD;
        
        if (dist < 0.0f) {
            collided = true;
            if (-dist < minPenetration) {
                minPenetration = -dist;
                contactPoint = worldCorner;
            }
        }
    }
    
    if (collided) {
        Contact contact;
        contact.position = contactPoint;
        contact.normal = planeNormal;
        contact.penetration = minPenetration;
        manifold.contacts.push_back(contact);

        return manifold;
    }
    return std::nullopt;
}

std::optional<ManifoldPoints> TestSphereBox(
        const components::Collider& c1, const ecs::components::Transform& t1,
        const components::Collider& c2, const ecs::components::Transform& t2) {
    
    auto* sc = dynamic_cast<const components::colliders::SphereCollider*>(&c1);
    auto* bc = dynamic_cast<const components::colliders::BoxCollider*>(&c2);
    
    if (!sc || !bc) {
        LogWrongCollisionTest("TestSphereBox", c1, c2);
        return std::nullopt;
    }

    glm::vec3 sphereCenter = t1.getPosition();
    float radius = sc->getGeometry().getRadius();
    glm::vec3 boxMin = t2.getPosition() + bc->getGeometry().getMin();
    glm::vec3 boxMax = t2.getPosition() + bc->getGeometry().getMax();

    // Clamp sphere center to box
    glm::vec3 closestPoint = glm::clamp(sphereCenter, boxMin, boxMax);
    glm::vec3 delta = sphereCenter - closestPoint;
    float dist2 = glm::dot(delta, delta);

    if (dist2 > radius * radius) {
        return std::nullopt;
    }

    ManifoldPoints manifold;
    float dist = glm::sqrt(dist2);
    
    Contact contact;
    if (dist > 0.0f) {
        contact.position = closestPoint;
        contact.normal = glm::normalize(delta);
        contact.penetration = radius - dist;
    } else {
        // Sphere center is inside box
        contact.position = sphereCenter;
        contact.normal = glm::vec3(1, 0, 0); // Default direction if inside
        contact.penetration = radius;
    }
    
    manifold.contacts.push_back(contact);
    return manifold;
}

std::optional<ManifoldPoints> TestSpherePlane(
        const components::Collider& c1, const ecs::components::Transform& t1,
        const components::Collider& c2, const ecs::components::Transform& t2) {
    
    auto* sc = dynamic_cast<const components::colliders::SphereCollider*>(&c1);
    auto* pc = dynamic_cast<const components::colliders::PlaneCollider*>(&c2);

    if (!sc || !pc) {
        LogWrongCollisionTest("TestSpherePlane", c1, c2);
        return std::nullopt;
    }

    glm::vec3 sphereCenter = t1.getPosition();
    float radius = sc->getGeometry().getRadius();
    glm::vec3 planeNormal = t2.getRotation() * pc->getGeometry().getNormal();
    float planeD = -glm::dot(planeNormal, t2.getPosition());

    float dist = glm::dot(planeNormal, sphereCenter) + planeD;

    if (dist > radius) {
        return std::nullopt;
    }

    ManifoldPoints manifold;
    Contact contact;
    contact.position = sphereCenter - planeNormal * dist;
    contact.normal = planeNormal;
    contact.penetration = radius - dist;
    manifold.contacts.push_back(contact);

    return manifold;
}

void LogWrongCollisionTest(
    const char* testName, 
    const components::Collider& c1, 
    const components::Collider& c2
) {
    spdlog::warn(
        "Wrong Collision Test Called: {}({}, {})", 
        testName, 
        static_cast<int>(c1.getType()), 
        static_cast<int>(c2.getType())
    );
}

} 