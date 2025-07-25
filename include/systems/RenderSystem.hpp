#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <core/Camera.hpp>
#include <core/Entity.hpp>
#include <core/Scene.hpp>
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
    void render(Scene& scene);
    void render(const Camera& camera, const Entity& entity) const;
    void render(
        const glm::mat4& projection,
        const glm::mat4& view,
        const glm::mat4& model,
        Entity& entity
    );
};

}