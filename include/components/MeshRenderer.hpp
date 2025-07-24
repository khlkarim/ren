#pragma once

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

    shaders::Shader& getShader();
    const shaders::Shader& getShader() const;
    void setShader(const shaders::Shader& shader);

    std::vector<shaders::Texture>& getTextures();
    void setTextures(const std::vector<shaders::Texture>& textures);

public:
    std::unique_ptr<shaders::Shader> shader;
    std::vector<shaders::Texture> textures;
};

}