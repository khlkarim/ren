#include "Sphere.hpp"
using ren::components::meshes::Sphere;
using ren::components::meshes::Vertex;

Sphere::Sphere() : Mesh(this->getVertices(), this->getIndices()) 
{
    spdlog::info("Sphere constructor");
}

Sphere::~Sphere()
{
    spdlog::info("Sphere destructor");
}

const std::vector<Vertex>& Sphere::getVertices() const
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

const std::vector<unsigned int>& Sphere::getIndices() const
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