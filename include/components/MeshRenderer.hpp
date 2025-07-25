#pragma once

#include <spdlog/spdlog.h>
#include <components/shaders/Shader.hpp>
#include <components/shaders/Texture.hpp>
#include <components/Component.hpp>
#include <utils/error_handler.hpp>

namespace ren::components 
{

class MeshRenderer : public Component
{
public:
    MeshRenderer(
        const shaders::Shader& shader,
        const std::vector<shaders::Texture>& textures
    );

    shaders::Shader& getShader();
    const shaders::Shader& getShader() const;
    void setShader(const shaders::Shader& shader);

    std::vector<shaders::Texture>& getTextures();
    void setTextures(const std::vector<shaders::Texture>& textures);

    std::unique_ptr<Component> clone() const override;

public:
    shaders::Shader shader;
    std::vector<shaders::Texture> textures;
};

}