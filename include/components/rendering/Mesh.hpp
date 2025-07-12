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
    void render(Shader& shader);

private:
    void init();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

private:
    unsigned int VAO, VBO, EBO;
};