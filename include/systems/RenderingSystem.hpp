#pragma once

#include <glm/glm.hpp>

namespace ren {
    class Entity;
    class Camera;
    namespace components {
        class Hierarchy;
    }
}

namespace ren::systems
{

class RenderingSystem
{
public:
    void render(
        const ren::Camera& camera, 
        const ren::components::Hierarchy& hierarchy
    ) const;
    void render(
        const ren::Entity& entity,
        const glm::mat4& projection = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f),
        const glm::mat4& model = glm::mat4(1.0f)
    ) const;
};

}