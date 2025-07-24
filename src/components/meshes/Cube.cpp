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
        { {1.0f, -1.0f, -1.0f}, glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f)), {0.0f, 0.0f} },
        { {1.0f, -1.0f,  1.0f}, glm::normalize(glm::vec3(1.0f, -1.0f,  1.0f)), {1.0f, 0.0f} },
        { {-1.0f, -1.0f,  1.0f}, glm::normalize(glm::vec3(-1.0f, -1.0f,  1.0f)), {1.0f, 1.0f} },
        { {-1.0f, -1.0f, -1.0f}, glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)), {0.0f, 1.0f} },
        { {1.0f,  1.0f, -1.0f}, glm::normalize(glm::vec3(1.0f,  1.0f, -1.0f)), {0.0f, 0.0f} },
        { {1.0f,  1.0f,  1.0f}, glm::normalize(glm::vec3(1.0f,  1.0f,  1.0f)), {1.0f, 0.0f} },
        { {-1.0f,  1.0f,  1.0f}, glm::normalize(glm::vec3(-1.0f,  1.0f,  1.0f)), {1.0f, 1.0f} },
        { {-1.0f,  1.0f, -1.0f}, glm::normalize(glm::vec3(-1.0f,  1.0f, -1.0f)), {0.0f, 1.0f} } 
    };
}

std::vector<unsigned int> Cube::getIndices() const
{
    return {
        0, 1, 2, 2, 3, 0,      
        4, 5, 1, 1, 0, 4,     
        7, 6, 5, 5, 4, 7,   
        3, 2, 6, 6, 7, 3,    
        4, 0, 3, 3, 7, 4,    
        1, 5, 6, 6, 2, 1      
    };
}