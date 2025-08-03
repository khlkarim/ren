#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <components/meshes/Cylinder.hpp>
using ren::components::meshes::Cylinder;
using ren::components::meshes::Vertex;

Cylinder::Cylinder(
    const float radius,
    const float height,
    const unsigned int segments,
    const unsigned int stacks
) : radius(radius), height(height), segments(segments), stacks(stacks), 
    Mesh(
        this->getVertices(radius, height, segments, stacks), 
        this->getIndices(radius, height, segments, stacks)
    )
{
    spdlog::info("Cylinder constructor");
}

Cylinder::~Cylinder()
{
    spdlog::info("Cylinder destructor");
}

std::vector<Vertex> Cylinder::getVertices(
    const float radius,
    const float height,
    const unsigned int segments,
    const unsigned int stacks
) {
    std::vector<Vertex> vertices;

    float theta_step = 180.0f / stacks;
    float phi_step = 360.0f / segments;

    for(unsigned int stack = 0; stack <= stacks; stack++) 
    {
        float theta = glm::radians(-90.0f + stack * theta_step);

        for (unsigned int segment = 0; segment <= segments; ++segment) 
        {
            float phi = glm::radians(segment * phi_step);
        
            Vertex vertex;
        
            vertex.Position = {
                radius * glm::cos(phi),
                height * glm::sin(theta),
                radius * glm::sin(phi)
            };
            vertex.Normal = glm::normalize(vertex.Position);
            vertex.TexCoords = glm::vec2(
                static_cast<float>(segment) / static_cast<float>(segments),
                static_cast<float>(stack) / static_cast<float>(stacks)
            );
        
            vertices.push_back(vertex);
        }
    }
    
    return vertices;
}

std::vector<unsigned int> Cylinder::getIndices(
    const float radius,
    const float height,
    const unsigned int segments,
    const unsigned int stacks
) {
    std::vector<unsigned int> indices;

    for(unsigned int stack = 0; stack < stacks; stack++) 
    {
        for(unsigned int segment = 0; segment < segments; segment++) 
        {
            int current = stack * (segments + 1) + segment;
            int next = (stack + 1) * (segments + 1) + segment;

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);

            indices.push_back(current + 1);
            indices.push_back(next);
            indices.push_back(next + 1);
        }
    }

    return indices;
}