#pragma once

#include <memory>

namespace ren::ecs::entities {
    class Entity;
    class EntityManager;
}

namespace ren::ecs::systems {

class System {
public:
    virtual ~System() = default;
    virtual void update(float dt, entities::EntityManager& entityManager) = 0;
    
    virtual std::unique_ptr<System> clone() const = 0;
};

} 