#include <ren/ecs/components/MeshRenderer.hpp>
using ren::ecs::components::Component;
using ren::ecs::components::MeshRenderer;
using namespace ren::ecs::components::shaders;

MeshRenderer::MeshRenderer(
    const Shader& shader,
    const std::vector<Texture>& textures
) {
    this->shader = shader;
    this->textures = textures;
}

void MeshRenderer::setShader(const Shader& shader)
{
    this->shader = shader;
}

Shader& MeshRenderer::getShader() 
{
    return this->shader;
}

const Shader& MeshRenderer::getShader() const
{
    return this->shader;
}

std::vector<Texture>& MeshRenderer::getTextures()
{
    return this->textures;
}

void MeshRenderer::setTextures(const std::vector<Texture>& textures)
{
    this->textures = textures;
}

std::unique_ptr<Component> MeshRenderer::clone() const {
    return std::make_unique<MeshRenderer>(*this);
}