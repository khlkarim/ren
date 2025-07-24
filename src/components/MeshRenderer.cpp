#include <components/MeshRenderer.hpp>
using ren::components::MeshRenderer;
using namespace ren::components::shaders;

MeshRenderer::MeshRenderer(
    const Shader& shader,
    const std::vector<Texture>& textures
) {
    this->shader = std::make_unique<Shader>(shader);
    this->textures = textures;
}
 
MeshRenderer::MeshRenderer(const MeshRenderer& other)
{
    this->shader = std::make_unique<Shader>(other.getShader());
    this->textures = other.textures;
}

void MeshRenderer::setShader(const Shader& shader)
{
    this->shader = std::make_unique<Shader>(shader);
}

Shader& MeshRenderer::getShader() 
{
    return *(this->shader);
}

const Shader& MeshRenderer::getShader() const
{
    return *(this->shader);
}

std::vector<Texture>& MeshRenderer::getTextures()
{
    return this->textures;
}

void MeshRenderer::setTextures(const std::vector<Texture>& textures)
{
    this->textures = textures;
}
