#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <ren/ecs/components/meshes/Sphere.hpp>
using ren::ecs::components::meshes::Sphere;
using ren::ecs::components::meshes::Vertex;

Sphere::Sphere(
    const float radius,
    const unsigned int segments,
    const unsigned int rings
) : radius(radius), segments(segments), rings(rings), 
    Mesh(
        this->getVertices(radius, segments, rings), 
        this->getIndices(radius, segments, rings)
    )
{
    spdlog::info("Sphere constructor");
}

Sphere::~Sphere()
{
    spdlog::info("Sphere destructor");
}

std::vector<Vertex> Sphere::getVertices(
    const float radius,
    const unsigned int segments,
    const unsigned int rings
) {
    std::vector<Vertex> vertices;

    float theta_step = 180.0f / rings;
    float phi_step = 360.0f / segments;

    for(unsigned int ring = 0; ring <= rings; ring++) 
    {
        float theta = glm::radians(-90.0f + ring * theta_step);

        for (unsigned int segment = 0; segment <= segments; ++segment) 
        {
            float phi = glm::radians(segment * phi_step);
        
            Vertex vertex;
        
            vertex.Position = {
                radius * glm::cos(theta) * glm::cos(phi),
                radius * glm::sin(theta),
                radius * glm::cos(theta) * glm::sin(phi)
            };
            vertex.Normal = glm::normalize(vertex.Position);
            vertex.TexCoords = glm::vec2(
                static_cast<float>(segment) / static_cast<float>(segments),
                static_cast<float>(ring) / static_cast<float>(rings)
            );
        
            vertices.push_back(vertex);
        }
    }
    
    return vertices;
}

std::vector<unsigned int> Sphere::getIndices(
    const float radius,
    const unsigned int segments,
    const unsigned int rings
) {
    std::vector<unsigned int> indices;

    for(unsigned int ring = 0; ring < rings; ring++) 
    {
        for(unsigned int segment = 0; segment < segments; segment++) 
        {
            int current = ring * (segments + 1) + segment;
            int next = (ring + 1) * (segments + 1) + segment;

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