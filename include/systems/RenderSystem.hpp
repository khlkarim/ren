#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <core/Camera.hpp>
#include <core/Entity.hpp>
#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <components/MeshRenderer.hpp>
#include <components/shaders/Shader.hpp>

namespace ren::systems
{

class RenderingSystem
{
public:
    void render(const Camera& camera, const Entity& entity);
};

}