#pragma once

#include <vector>
#include <glad/glad.h>
#include "Shader.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"


namespace ren::components::meshes {

class Mesh
{
public:
    Mesh(
        std::vector<Vertex> vertices,
        std::vector<unsigned int> indices,
        std::vector<ren::components::shaders::Texture> textures
    );
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

    std::shared_ptr<ren::components::shaders::Shader> getShader() const;
    void setShader(const std::shared_ptr<ren::components::shaders::Shader>& shader);

private:
    void init();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ren::components::shaders::Texture> textures;

private:
    std::shared_ptr<ren::components::shaders::Shader> shader;
    unsigned int VAO, VBO, EBO;
};

}
