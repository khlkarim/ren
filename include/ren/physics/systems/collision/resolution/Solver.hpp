#pragma once

namespace ren::physics::components { class RigidBody; }
namespace ren::physics::systems::collision { struct ManifoldPoints; }

namespace ren::physics::systems::collision::resolution {

class Solver {
public:
    void solve(
        const float dt, 
        components::RigidBody& r1, 
        components::RigidBody& r2, 
        ManifoldPoints& manifoldPoints
    );
};

}