#include "ecs/components/MeshRenderer.hpp"

namespace ren::ecs::components {

MeshRenderer::MeshRenderer(const shaders::Shader& shader)
    : m_shader(shader) {}

MeshRenderer::MeshRenderer(const shaders::Shader& shader,
                          const std::vector<shaders::Texture>& textures)
    : m_shader(shader), m_textures(textures) {}

void MeshRenderer::setShader(const shaders::Shader& shader) {
    m_shader = shader;
}

shaders::Shader& MeshRenderer::getShader() {
    return m_shader;
}

const shaders::Shader& MeshRenderer::getShader() const {
    return m_shader;
}

std::vector<shaders::Texture>& MeshRenderer::getTextures() {
    return m_textures;
}

const std::vector<shaders::Texture>& MeshRenderer::getTextures() const {
    return m_textures;
}

void MeshRenderer::setTextures(const std::vector<shaders::Texture>& textures) {
    m_textures = textures;
}

std::unique_ptr<Component> MeshRenderer::clone() const {
    return std::make_unique<MeshRenderer>(*this);
}

} 
