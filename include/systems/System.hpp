#pragma once

#include <memory>

namespace ren
{
    class Scene;
}

namespace ren::systems
{

class System
{
public:
    virtual void update(const float dt, Scene& scene) = 0;
    virtual std::unique_ptr<System> clone() const = 0;
};

}