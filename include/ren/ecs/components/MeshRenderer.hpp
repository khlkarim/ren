#pragma once

#include <ren/ecs/components/Component.hpp>
#include <ren/ecs/components/shaders/Shader.hpp>
#include <ren/ecs/components/shaders/Texture.hpp>

namespace ren::ecs::components 
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