#pragma once

#include "ecs/components/Component.hpp"

namespace ren::physics::components
{

class Collider : public ecs::components::Component
{
public:
    enum class Type {
        Box,
        Sphere,
        Mesh
    };
    virtual ~Collider() = default;
    
    virtual Type getType() const = 0;
    const bool getIsTrigger() const;
    void setIsTrigger(bool isTrigger);

protected:
    bool isTrigger = false;
};


}