#pragma once

#include "ecs/components/Component.hpp"

namespace ren::physics::components
{

class Collider : public ecs::components::Component
{
public:
    enum class Type {
        Box,
        Plane,
        Sphere,
        Count
    };
    virtual ~Collider() = default;
    
    Type getType() const;

    bool getIsTrigger() const;
    void setIsTrigger(bool isTrigger);

protected:
    Type m_type;
    bool m_isTrigger = false;
};


}