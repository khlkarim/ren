#include "Cube.hpp"
using ren::components::meshes::Cube;
using ren::components::meshes::Vertex;

Cube::Cube() : Mesh(this->getVertices(), this->getIndices()) 
{
    spdlog::info("Cube constructor");
}

Cube::~Cube()
{
    spdlog::info("Cube destructor");
}

std::vector<Vertex> Cube::getVertices() const
{
    return {
        // Front face
        { {1.0f,  1.0f,  1.0f},  {0.0f, 0.0f, 1.0f} },
        { {-1.0f, 1.0f,  1.0f},  {0.0f, 0.0f, 1.0f} },
        { {-1.0f,-1.0f,  1.0f},  {0.0f, 0.0f, 1.0f} },
        { {1.0f, -1.0f,  1.0f},  {0.0f, 0.0f, 1.0f} },

        // Right face
        { {1.0f,  1.0f,  1.0f},  {1.0f, 0.0f, 0.0f} },
        { {1.0f, -1.0f,  1.0f},  {1.0f, 0.0f, 0.0f} },
        { {1.0f, -1.0f, -1.0f},  {1.0f, 0.0f, 0.0f} },
        { {1.0f,  1.0f, -1.0f},  {1.0f, 0.0f, 0.0f} },

        // Top face
        { {1.0f,  1.0f,  1.0f},  {0.0f, 1.0f, 0.0f} },
        { {1.0f,  1.0f, -1.0f},  {0.0f, 1.0f, 0.0f} },
        { {-1.0f, 1.0f, -1.0f},  {0.0f, 1.0f, 0.0f} },
        { {-1.0f, 1.0f,  1.0f},  {0.0f, 1.0f, 0.0f} },

        // Left face
        { {-1.0f, 1.0f,  1.0f},  {-1.0f, 0.0f, 0.0f} },
        { {-1.0f, 1.0f, -1.0f},  {-1.0f, 0.0f, 0.0f} },
        { {-1.0f,-1.0f, -1.0f},  {-1.0f, 0.0f, 0.0f} },
        { {-1.0f,-1.0f,  1.0f},  {-1.0f, 0.0f, 0.0f} },

        // Bottom face
        { {-1.0f,-1.0f, -1.0f},  {0.0f, -1.0f, 0.0f} },
        { {1.0f, -1.0f, -1.0f},  {0.0f, -1.0f, 0.0f} },
        { {1.0f, -1.0f,  1.0f},  {0.0f, -1.0f, 0.0f} },
        { {-1.0f,-1.0f,  1.0f},  {0.0f, -1.0f, 0.0f} },

        // Back face
        { {1.0f, -1.0f, -1.0f},  {0.0f, 0.0f, -1.0f} },
        { {-1.0f,-1.0f, -1.0f},  {0.0f, 0.0f, -1.0f} },
        { {-1.0f, 1.0f, -1.0f},  {0.0f, 0.0f, -1.0f} },
        { {1.0f,  1.0f, -1.0f},  {0.0f, 0.0f, -1.0f} }
    };
}

std::vector<unsigned int> Cube::getIndices() const
{
    return {
        // Front face
        0, 1, 2,
        0, 2, 3,

        // Right face
        4, 5, 6,
        4, 6, 7,

        // Top face
        8, 9, 10,
        8, 10, 11,

        // Left face
        12, 13, 14,
        12, 14, 15,

        // Bottom face
        16, 17, 18,
        16, 18, 19,

        // Back face
        20, 21, 22,
        20, 22, 23
    };
}