#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "ecs/components/meshes/Sphere.hpp"

namespace ren::ecs::components::meshes {

Sphere::Sphere(float radius, unsigned int segments, unsigned int rings)
    : Mesh(getVertices(radius, segments, rings), 
           getIndices(segments, rings)),
      m_radius(radius),
      m_segments(segments),
      m_rings(rings)
{
    spdlog::info("Sphere constructor");
}

Sphere::~Sphere()
{
    spdlog::info("Sphere destructor");
}

std::vector<Vertex> Sphere::getVertices(float radius, unsigned int segments, unsigned int rings)
{
    std::vector<Vertex> vertices;
    vertices.reserve((rings + 1) * (segments + 1));

    const float thetaStep = glm::radians(180.0f / rings);
    const float phiStep = glm::radians(360.0f / segments);

    for (unsigned int ring = 0; ring <= rings; ++ring) 
    {
        const float theta = glm::radians(-90.0f + ring * 180.0f / rings);
        const float sinTheta = glm::sin(theta);
        const float cosTheta = glm::cos(theta);

        for (unsigned int segment = 0; segment <= segments; ++segment) 
        {
            const float phi = segment * phiStep;
            const float cosPhi = glm::cos(phi);
            const float sinPhi = glm::sin(phi);
        
            Vertex vertex;
            // Calculate position on sphere
            vertex.Position = {
                radius * cosTheta * cosPhi,
                radius * sinTheta,
                radius * cosTheta * sinPhi
            };
            // Normal is just the normalized position for a sphere
            vertex.Normal = glm::normalize(vertex.Position);
            // UV coordinates mapped to sphere
            vertex.TexCoords = {
                static_cast<float>(segment) / segments,
                static_cast<float>(ring) / rings
            };
        
            vertices.push_back(vertex);
        }
    }
    
    return vertices;
}

std::vector<unsigned int> Sphere::getIndices(unsigned int segments, unsigned int rings)
{
    std::vector<unsigned int> indices;
    indices.reserve(rings * segments * 6);

    for (unsigned int ring = 0; ring < rings; ++ring) 
    {
        for (unsigned int segment = 0; segment < segments; ++segment) 
        {
            const unsigned int current = ring * (segments + 1) + segment;
            const unsigned int next = (ring + 1) * (segments + 1) + segment;

            // First triangle
            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);

            // Second triangle
            indices.push_back(current + 1);
            indices.push_back(next);
            indices.push_back(next + 1);
        }
    }

    return indices;
}

float Sphere::getRadius() const
{
    return m_radius;
}

void Sphere::setRadius(float radius)
{
    m_radius = radius;
    reinitialize();
}

unsigned int Sphere::getSegments() const
{
    return m_segments;
}

void Sphere::setSegments(unsigned int segments)
{
    m_segments = segments;
    reinitialize();
}

unsigned int Sphere::getRings() const
{
    return m_rings;
}

void Sphere::setRings(unsigned int rings)
{
    m_rings = rings;
    reinitialize();
}

void Sphere::reinitialize()
{
    m_vertices = getVertices(m_radius, m_segments, m_rings);
    m_indices = getIndices(m_segments, m_rings);
    Mesh::reinitialize();
}

}