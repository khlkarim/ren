#pragma once

#include <vector>
#include <glad/glad.h>
#include "Shader.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"

class Mesh
{
public:
    Mesh(
        std::vector<Vertex> vertices, 
        std::vector<unsigned int> indices, 
        std::vector<Texture> textures
    );
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

    std::shared_ptr<Shader> getShader() const;
    void setShader(const std::shared_ptr<Shader>& shader);

private:
    void init();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

private:
    std::shared_ptr<Shader> shader;
    unsigned int VAO, VBO, EBO;
};