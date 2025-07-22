#pragma once

#include <vector>
#include <glad/glad.h>
#include "Shader.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include <components/Component.hpp>

namespace ren::components
{

class Mesh : public Component
{
public:
    Mesh(
        std::vector<meshes::Vertex> vertices,
        std::vector<unsigned int> indices,
        std::vector<shaders::Texture> textures
    );
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

    std::shared_ptr<shaders::Shader> getShader() const;
    void setShader(const std::shared_ptr<shaders::Shader>& shader);

private:
    void init();

public:
    std::vector<meshes::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<shaders::Texture> textures;

private:
    std::shared_ptr<shaders::Shader> shader;
    unsigned int VAO, VBO, EBO;
};

}
