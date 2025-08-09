#include "ecs/components/Transform.hpp"
#include "physics/components/colliders/BoxCollider.hpp"
#include "physics/components/colliders/SphereCollider.hpp"
#include "physics/systems/collision/ManifoldPoints.hpp"
#include "physics/systems/collision/detection/broad.hpp"

namespace ren::physics::systems::collision::detection::broad {

namespace {
constexpr float EPSILON = 1e-6f;

// Helper function to create a simple contact manifold
ManifoldPoints createSingleContactManifold(const glm::vec3& position, 
                                          const glm::vec3& normal,
                                          float penetration) {
    ManifoldPoints manifold;
    Contact contact;
    contact.position = position;
    contact.normal = normal;
    contact.penetration = penetration;
    manifold.contacts.push_back(contact);
    return manifold;
}
} // anonymous namespace

std::optional<ManifoldPoints> AABB(
    const components::colliders::BoxCollider& c1,
    const ecs::components::Transform& t1,
    const components::colliders::BoxCollider& c2,
    const ecs::components::Transform& t2
) {
    const auto& pos1 = t1.getPosition();
    const auto& pos2 = t2.getPosition();
    const auto& he1 = c1.getGeometry().getHalfExtents();
    const auto& he2 = c2.getGeometry().getHalfExtents();

    // Calculate min/max bounds for both boxes
    glm::vec3 min1 = pos1 - he1;
    glm::vec3 max1 = pos1 + he1;
    glm::vec3 min2 = pos2 - he2;
    glm::vec3 max2 = pos2 + he2;

    // Check for overlap along each axis
    bool overlapX = (min1.x <= max2.x) && (max1.x >= min2.x);
    bool overlapY = (min1.y <= max2.y) && (max1.y >= min2.y);
    bool overlapZ = (min1.z <= max2.z) && (max1.z >= min2.z);

    // Early exit if no overlap
    if (!(overlapX && overlapY && overlapZ)) {
        return std::nullopt;
    }

    // Calculate penetration depth along each axis
    float px = std::min(max1.x, max2.x) - std::max(min1.x, min2.x);
    float py = std::min(max1.y, max2.y) - std::max(min1.y, min2.y);
    float pz = std::min(max1.z, max2.z) - std::max(min1.z, min2.z);

    // Find minimum penetration axis
    float penetration = px;
    glm::vec3 normal(1, 0, 0);

    if (py < penetration) {
        penetration = py;
        normal = glm::vec3(0, 1, 0);
    }
    if (pz < penetration) {
        penetration = pz;
        normal = glm::vec3(0, 0, 1);
    }

    // Ensure normal points from box1 to box2
    glm::vec3 centerDelta = pos2 - pos1;
    if (glm::dot(centerDelta, normal) < 0) {
        normal = -normal;
    }

    // Calculate contact point
    glm::vec3 contactPoint = 0.5f * (glm::clamp(pos1, min2, max2) + glm::clamp(pos2, min1, max1));

    return createSingleContactManifold(contactPoint, normal, penetration);
}

std::optional<ManifoldPoints> OBB(
    const components::colliders::BoxCollider& c1,
    const ecs::components::Transform& t1,
    const components::colliders::BoxCollider& c2,
    const ecs::components::Transform& t2
) {
    // Get positions and orientations
    const glm::vec3& pos1 = t1.getPosition();
    const glm::vec3& pos2 = t2.getPosition();
    const glm::mat3& rot1 = t1.getRotationMatrix();
    const glm::mat3& rot2 = t2.getRotationMatrix();
    const glm::vec3& he1 = c1.getGeometry().getHalfExtents();
    const glm::vec3& he2 = c2.getGeometry().getHalfExtents();

    // Compute rotation matrix expressing box2 in box1's coordinate frame
    glm::mat3 R;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            R[i][j] = glm::dot(rot1[i], rot2[j]);
        }
    }

    // Compute translation vector t (box2 relative to box1)
    glm::vec3 t = pos2 - pos1;
    // Bring translation into box1's frame
    t = glm::vec3(glm::dot(t, rot1[0]), glm::dot(t, rot1[1]), glm::dot(t, rot1[2]));

    // Compute absolute rotation matrix with epsilon to handle parallel edges
    glm::mat3 AbsR;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            AbsR[i][j] = std::abs(R[i][j]) + EPSILON;
        }
    }

    // Test all 15 potential separating axes
    
    // Test axes L = A0, A1, A2 (box1 face normals)
    for (int i = 0; i < 3; ++i) {
        float ra = he1[i];
        float rb = he2.x * AbsR[i][0] + he2.y * AbsR[i][1] + he2.z * AbsR[i][2];
        if (std::abs(t[i]) > ra + rb)
            return std::nullopt;
    }

    // Test axes L = B0, B1, B2 (box2 face normals)
    for (int i = 0; i < 3; ++i) {
        float ra = he1.x * AbsR[0][i] + he1.y * AbsR[1][i] + he1.z * AbsR[2][i];
        float rb = he2[i];
        float proj = std::abs(t.x * R[0][i] + t.y * R[1][i] + t.z * R[2][i]);
        if (proj > ra + rb)
            return std::nullopt;
    }

    // Test 9 edge cross products: A0 x B0, A0 x B1, A0 x B2, A1 x B0, ..., A2 x B2
    
    // A0 x B0
    float ra = he1.y * AbsR[2][0] + he1.z * AbsR[1][0];
    float rb = he2.y * AbsR[0][2] + he2.z * AbsR[0][1];
    if (std::abs(t.z * R[1][0] - t.y * R[2][0]) > ra + rb) 
        return std::nullopt;

    // A0 x B1
    ra = he1.y * AbsR[2][1] + he1.z * AbsR[1][1];
    rb = he2.x * AbsR[0][2] + he2.z * AbsR[0][0];
    if (std::abs(t.z * R[1][1] - t.y * R[2][1]) > ra + rb) 
        return std::nullopt;

    // A0 x B2
    ra = he1.y * AbsR[2][2] + he1.z * AbsR[1][2];
    rb = he2.x * AbsR[0][1] + he2.y * AbsR[0][0];
    if (std::abs(t.z * R[1][2] - t.y * R[2][2]) > ra + rb) 
        return std::nullopt;

    // A1 x B0
    ra = he1.x * AbsR[2][0] + he1.z * AbsR[0][0];
    rb = he2.y * AbsR[1][2] + he2.z * AbsR[1][1];
    if (std::abs(t.x * R[2][0] - t.z * R[0][0]) > ra + rb) 
        return std::nullopt;

    // A1 x B1
    ra = he1.x * AbsR[2][1] + he1.z * AbsR[0][1];
    rb = he2.x * AbsR[1][2] + he2.z * AbsR[1][0];
    if (std::abs(t.x * R[2][1] - t.z * R[0][1]) > ra + rb) 
        return std::nullopt;

    // A1 x B2
    ra = he1.x * AbsR[2][2] + he1.z * AbsR[0][2];
    rb = he2.x * AbsR[1][1] + he2.y * AbsR[1][0];
    if (std::abs(t.x * R[2][2] - t.z * R[0][2]) > ra + rb) 
        return std::nullopt;

    // A2 x B0
    ra = he1.x * AbsR[1][0] + he1.y * AbsR[0][0];
    rb = he2.y * AbsR[2][2] + he2.z * AbsR[2][1];
    if (std::abs(t.y * R[0][0] - t.x * R[1][0]) > ra + rb) 
        return std::nullopt;

    // A2 x B1
    ra = he1.x * AbsR[1][1] + he1.y * AbsR[0][1];
    rb = he2.x * AbsR[2][2] + he2.z * AbsR[2][0];
    if (std::abs(t.y * R[0][1] - t.x * R[1][1]) > ra + rb) 
        return std::nullopt;

    // A2 x B2
    ra = he1.x * AbsR[1][2] + he1.y * AbsR[0][2];
    rb = he2.x * AbsR[2][1] + he2.y * AbsR[2][0];
    if (std::abs(t.y * R[0][2] - t.x * R[1][2]) > ra + rb) 
        return std::nullopt;

    // Boxes are intersecting - for broad phase, return simplified contact info
    glm::vec3 normal = glm::normalize(pos2 - pos1);
    glm::vec3 contactPos = 0.5f * (pos1 + pos2);
    
    // Penetration is not trivial for OBBs, set to a small value for broad phase
    float penetration = 0.01f;
    
    return createSingleContactManifold(contactPos, normal, penetration);
}

std::optional<ManifoldPoints> BoundingSpheres(
    const components::colliders::SphereCollider& c1,
    const ecs::components::Transform& t1,
    const components::colliders::SphereCollider& c2,
    const ecs::components::Transform& t2
) {
    const auto& pos1 = t1.getPosition();
    const auto& pos2 = t2.getPosition();
    float r1 = c1.getGeometry().getRadius();
    float r2 = c2.getGeometry().getRadius();

    // Calculate vector from sphere1 to sphere2
    glm::vec3 delta = pos2 - pos1;
    float distSquared = glm::dot(delta, delta);
    float radiusSum = r1 + r2;
    
    // Early out - check squared distance against squared radius sum
    if (distSquared > radiusSum * radiusSum) {
        return std::nullopt;
    }
    
    float dist = std::sqrt(distSquared);
    
    // Handle case where spheres are at the same position
    glm::vec3 normal;
    if (dist < EPSILON) {
        normal = glm::vec3(0, 1, 0); // Arbitrary normal
        dist = EPSILON;
    } else {
        normal = delta / dist;
    }
    
    // Contact point is on the surface of the first sphere along the direction to the second sphere
    glm::vec3 contactPos = pos1 + normal * r1;
    float penetration = radiusSum - dist;
    
    return createSingleContactManifold(contactPos, normal, penetration);
}

} // namespace ren::physics::systems::collision::detection::broad