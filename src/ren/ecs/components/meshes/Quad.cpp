#include "ecs/components/meshes/Quad.hpp"
#include <spdlog/spdlog.h>

namespace ren::ecs::components::meshes {

Quad::Quad(float width, float height, unsigned int widthSegments, unsigned int heightSegments)
    : Mesh(getVertices(width, height, widthSegments, heightSegments), 
           getIndices(width, height, widthSegments, heightSegments)),
      m_width(width), 
      m_height(height), 
      m_widthSegments(widthSegments), 
      m_heightSegments(heightSegments)
{
    spdlog::info("Quad constructor");
}

Quad::~Quad()
{
    spdlog::info("Quad destructor");
}

float Quad::getWidth() const 
{
    return m_width;
}

float Quad::getHeight() const 
{
    return m_height;
}

unsigned int Quad::getWidthSegments() const 
{
    return m_widthSegments;
}

unsigned int Quad::getHeightSegments() const 
{
    return m_heightSegments;
}

void Quad::setWidth(float width) 
{
    m_width = width;
    reinitialize();
}

void Quad::setHeight(float height) 
{
    m_height = height;
    reinitialize();
}

void Quad::setWidthSegments(unsigned int widthSegments) 
{
    m_widthSegments = widthSegments;
    reinitialize();
}

void Quad::setHeightSegments(unsigned int heightSegments) 
{
    m_heightSegments = heightSegments;
    reinitialize();
}

void Quad::reinitialize()
{
    m_vertices = getVertices(m_width, m_height, m_widthSegments, m_heightSegments);
    m_indices = getIndices(m_width, m_height, m_widthSegments, m_heightSegments);
    Mesh::reinitialize();
}

std::vector<Vertex> Quad::getVertices(float width, float height, 
                                      unsigned int widthSegments, 
                                      unsigned int heightSegments)
{
    const unsigned int vertexCols = static_cast<unsigned int>(width * widthSegments);
    const unsigned int vertexRows = static_cast<unsigned int>(height * heightSegments);
    
    std::vector<Vertex> vertices;
    vertices.reserve((vertexCols + 1) * (vertexRows + 1));

    const float dx = 1.0f / widthSegments;
    const float dy = 1.0f / heightSegments;
    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;

    for (unsigned int y = 0; y <= vertexRows; ++y)
    {
        for (unsigned int x = 0; x <= vertexCols; ++x)
        {
            Vertex vertex;
            
            vertex.Position = glm::vec3(
                x * dx - halfWidth,
                y * dy - halfHeight,
                0.0f
            );
            vertex.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
            vertex.TexCoords = glm::vec2(
                static_cast<float>(x) / static_cast<float>(vertexCols),
                static_cast<float>(y) / static_cast<float>(vertexRows)
            );

            vertices.push_back(vertex);
        }
    }

    return vertices;
}

std::vector<unsigned int> Quad::getIndices(float width, float height,
                                          unsigned int widthSegments,
                                          unsigned int heightSegments)
{
    const unsigned int vertexCols = static_cast<unsigned int>(width * widthSegments);
    const unsigned int vertexRows = static_cast<unsigned int>(height * heightSegments);
    const unsigned int rowStride = vertexCols + 1;
    
    // Pre-allocate space for indices (2 triangles per quad, 3 indices per triangle)
    std::vector<unsigned int> indices;
    indices.reserve(vertexRows * vertexCols * 6);

    for (unsigned int y = 0; y < vertexRows; ++y)
    {
        for (unsigned int x = 0; x < vertexCols; ++x)
        {
            const unsigned int bottomLeft = y * rowStride + x;
            const unsigned int bottomRight = bottomLeft + 1;
            const unsigned int topLeft = bottomLeft + rowStride;
            const unsigned int topRight = topLeft + 1;

            // First triangle (bottom-right triangle)
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);

            // Second triangle (top-left triangle)
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topLeft);
        }
    }

    return indices;
}

} 