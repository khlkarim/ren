#pragma once

#include <string>
#include <core/Camera.hpp>
#include <components/Hierarchy.hpp> 

namespace ren {

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    Camera& getCamera();
    const Camera& getCamera() const;
    void setCamera(const Camera& camera);

    components::Hierarchy& getHierarchy();
    const components::Hierarchy& getHierarchy() const;
    void setHierarchy(const components::Hierarchy& hierarchy);

    void render();

private:
    Camera camera;
    components::Hierarchy hierarchy;
};

}