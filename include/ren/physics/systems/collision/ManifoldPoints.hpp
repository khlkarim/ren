#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace ren::physics::systems::collision
{

struct Contact {
    glm::vec3 position;
    float penetration = 0.0f;
    glm::vec3 normal = {0.0f, 0.0f, 0.0f};
};  

// The points of contact between two bodies
struct ManifoldPoints {
    std::vector<Contact> contacts;
};

}