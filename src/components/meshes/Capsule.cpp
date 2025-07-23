#include "Capsule.hpp"
using ren::components::meshes::Capsule;
using ren::components::meshes::Vertex;

Capsule::Capsule() : Mesh(this->getVertices(), this->getIndices()) 
{
    spdlog::info("Capsule constructor");
}

Capsule::~Capsule()
{
    spdlog::info("Capsule destructor");
}

const std::vector<Vertex>& Capsule::getVertices() const
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

const std::vector<unsigned int>& Capsule::getIndices() const
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