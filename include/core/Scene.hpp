#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include <core/Camera.hpp>
#include <core/Entity.hpp>
#include <utils/error_handler.hpp>
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

private:
    Camera camera;
    components::Hierarchy hierarchy;
};

}