#pragma once

namespace ren::ecs::components {
    class Transform;
}

namespace ren::physics::components {
    class RigidBody;
}

namespace ren::physics::systems::dynamics {

class Solver {
public:
    void solve(
        const float dt, 
        components::RigidBody& rigidBody, 
        ecs::components::Transform& transform
    );
};

} 