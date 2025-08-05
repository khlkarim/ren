#pragma once

#include <string>
#include <ren/ecs/components/Hierarchy.hpp> 

namespace ren::core
{

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    ecs::components::Hierarchy& getHierarchy();
    const ecs::components::Hierarchy& getHierarchy() const;
    void setHierarchy(const ecs::components::Hierarchy& hierarchy);

private:
    ecs::components::Hierarchy hierarchy;
};

}