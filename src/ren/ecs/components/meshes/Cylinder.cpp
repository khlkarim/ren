#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "ecs/components/meshes/Cylinder.hpp"

namespace ren::ecs::components::meshes {

Cylinder::Cylinder(
    float radius,
    float height,
    unsigned int segments,
    unsigned int stacks
) : 
    m_radius(radius), 
    m_height(height), 
    m_segments(segments), 
    m_stacks(stacks), 
    Mesh(
        getVertices(radius, height, segments, stacks), 
        getIndices(segments, stacks)
    )
{
    spdlog::info("Cylinder constructor");
}

Cylinder::~Cylinder()
{
    spdlog::info("Cylinder destructor");
}

std::vector<Vertex> Cylinder::getVertices(
    float radius,
    float height,
    unsigned int segments,
    unsigned int stacks
) {
    std::vector<Vertex> vertices;
    vertices.reserve((segments + 1) * (stacks + 1));

    const float thetaStep = 180.0f / stacks;
    const float phiStep = 360.0f / segments;

    for (unsigned int stack = 0; stack <= stacks; ++stack) 
    {
        float theta = glm::radians(-90.0f + stack * thetaStep);

        for (unsigned int segment = 0; segment <= segments; ++segment) 
        {
            float phi = glm::radians(segment * phiStep);
        
            Vertex vertex;
            vertex.Position = {
                radius * glm::cos(phi),
                height * glm::sin(theta),
                radius * glm::sin(phi)
            };
            vertex.Normal = glm::normalize(vertex.Position);
            vertex.TexCoords = {
                static_cast<float>(segment) / static_cast<float>(segments),
                static_cast<float>(stack) / static_cast<float>(stacks)
            };
        
            vertices.push_back(vertex);
        }
    }
    
    return vertices;
}

std::vector<unsigned int> Cylinder::getIndices(
    unsigned int segments,
    unsigned int stacks
)  {
    std::vector<unsigned int> indices;
    indices.reserve(6 * segments * stacks);

    for (unsigned int stack = 0; stack < stacks; ++stack) 
    {
        for (unsigned int segment = 0; segment < segments; ++segment) 
        {
            unsigned int current = stack * (segments + 1) + segment;
            unsigned int next = (stack + 1) * (segments + 1) + segment;

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

float Cylinder::getRadius() const {
    return m_radius;
}

float Cylinder::getHeight() const {
    return m_height;
}

unsigned int Cylinder::getSegments() const {
    return m_segments;
}

unsigned int Cylinder::getStacks() const {
    return m_stacks;
}

void Cylinder::setRadius(float radius) {
    m_radius = radius;
    reinitialize();
}

void Cylinder::setHeight(float height) {
    m_height = height;
    reinitialize();
}

void Cylinder::setSegments(unsigned int segments) {
    m_segments = segments;
    reinitialize();
}

void Cylinder::setStacks(unsigned int stacks) {
    m_stacks = stacks;
    reinitialize();
}

void Cylinder::reinitialize() {
    m_vertices = getVertices(m_radius, m_height, m_segments, m_stacks);
    m_indices = getIndices(m_segments, m_stacks);
    Mesh::reinitialize();
}

}