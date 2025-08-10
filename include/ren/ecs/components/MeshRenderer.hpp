#pragma once

#include <memory>
#include <vector>
#include "ecs/components/Component.hpp"
#include "ecs/components/shaders/Shader.hpp"
#include "ecs/components/shaders/Texture.hpp"

namespace ren::ecs::components 
{

class MeshRenderer : public Component
{
public:
    explicit MeshRenderer(const shaders::Shader& shader);
    MeshRenderer(const shaders::Shader& shader, const std::vector<shaders::Texture>& textures);

    shaders::Shader& getShader();
    const shaders::Shader& getShader() const;
    void setShader(const shaders::Shader& newShader);

    std::vector<shaders::Texture>& getTextures();
    const std::vector<shaders::Texture>& getTextures() const;
    void setTextures(const std::vector<shaders::Texture>& newTextures);

    std::unique_ptr<Component> clone() const override;

private:
    shaders::Shader m_shader;
    std::vector<shaders::Texture> m_textures;
};

}