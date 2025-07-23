#pragma once

#include <optional>
#include <spdlog/spdlog.h>
#include <components/shaders/Shader.hpp>
#include <components/shaders/Texture.hpp>

namespace ren::components 
{

class MeshRenderer
{
public:
    MeshRenderer(
        const Shader& shader,
        const std::vector<shaders::Texture>& textures
    );
    MeshRenderer(const MeshRenderer& other);

    void setShader(const Shader& shader);
    const Shader& getShader() const;

    void setTextures(const std::vector<shaders::Texture>& textures);
    const const std::vector<shaders::Texture>& getTextures();

public:
    std::unique_ptr<shaders::Shader> shader;
    std::vector<shaders::Texture> textures;
};

}