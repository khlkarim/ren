#include "Cylinder.hpp"
using ren::components::meshes::Cylinder;
using ren::components::meshes::Vertex;

Cylinder::Cylinder() : Mesh(this->getVertices(), this->getIndices()) 
{
    spdlog::info("Cylinder constructor");
}

Cylinder::~Cylinder()
{
    spdlog::info("Cylinder destructor");
}

std::vector<Vertex> Cylinder::getVertices() const
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

std::vector<unsigned int> Cylinder::getIndices() const
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