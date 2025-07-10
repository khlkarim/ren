#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
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
    void render();

private:
    void init();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

private:
    unsigned int VAO, VBO, EBO;
};

#endif