#include "Cube.hpp"
using ren::components::meshes::Cube;
using ren::components::meshes::Vertex;
using ren::components::shaders::Texture;

Cube::Cube() : Mesh(this->getVertices(), this->getIndices(), this->getTextures()) {}

const std::vector<Vertex>& Cube::getVertices() const
{
    return {
        // Vertex positions and normals for a cube (normal = normalized position)
        { {1.0f, -1.0f, -1.0f}, glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f)), {0.0f, 0.0f} }, // 0
        { {1.0f, -1.0f,  1.0f}, glm::normalize(glm::vec3(1.0f, -1.0f,  1.0f)), {1.0f, 0.0f} }, // 1
        { {-1.0f, -1.0f,  1.0f}, glm::normalize(glm::vec3(-1.0f, -1.0f,  1.0f)), {1.0f, 1.0f} }, // 2
        { {-1.0f, -1.0f, -1.0f}, glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)), {0.0f, 1.0f} }, // 3
        { {1.0f,  1.0f, -1.0f}, glm::normalize(glm::vec3(1.0f,  1.0f, -1.0f)), {0.0f, 0.0f} }, // 4
        { {1.0f,  1.0f,  1.0f}, glm::normalize(glm::vec3(1.0f,  1.0f,  1.0f)), {1.0f, 0.0f} }, // 5
        { {-1.0f,  1.0f,  1.0f}, glm::normalize(glm::vec3(-1.0f,  1.0f,  1.0f)), {1.0f, 1.0f} }, // 6
        { {-1.0f,  1.0f, -1.0f}, glm::normalize(glm::vec3(-1.0f,  1.0f, -1.0f)), {0.0f, 1.0f} }  // 7
    };
}

const std::vector<unsigned int>& Cube::getIndices() const
{
    return {
        0, 1, 2, 2, 3, 0,       // Bottom face
        4, 5, 1, 1, 0, 4,       // Right face
        7, 6, 5, 5, 4, 7,       // Top face
        3, 2, 6, 6, 7, 3,       // Left face
        4, 0, 3, 3, 7, 4,       // Back face
        1, 5, 6, 6, 2, 1        // Front face
    };
}