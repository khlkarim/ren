#pragma once

#include <optional>
#include <spdlog/spdlog.h>
#include <components/shaders/Shader.hpp>
#include <components/shaders/Texture.hpp>
#include <components/Component.hpp>

namespace ren::components 
{

class MeshRenderer : public Component
{
public:
    MeshRenderer(
        const shaders::Shader& shader,
        const std::vector<shaders::Texture>& textures
    );
    MeshRenderer(const MeshRenderer& other);

    void setShader(const shaders::Shader& shader);
    const shaders::Shader& getShader() const;

    void setTextures(const std::vector<shaders::Texture>& textures);
    const std::vector<shaders::Texture>& getTextures();

public:
    std::unique_ptr<shaders::Shader> shader;
    std::vector<shaders::Texture> textures;
};

}