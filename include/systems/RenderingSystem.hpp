#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <core/Camera.hpp>
#include <core/Entity.hpp>
#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <components/MeshRenderer.hpp>
#include <components/Hierarchy.hpp>
#include <components/shaders/Shader.hpp>

namespace ren::systems
{

class RenderingSystem
{
public:
    void render(
        const Camera& camera, 
        const components::Hierarchy& hierarchy
    ) const;
    void render(
        const Entity& entity,
        const glm::mat4& projection = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f),
        const glm::mat4& model = glm::mat4(1.0f)
    ) const;
};

}