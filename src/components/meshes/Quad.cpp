#include "Quad.hpp"
using ren::components::meshes::Quad;
using ren::components::meshes::Vertex;

Quad::Quad(
    const float width,
    const float height,
    const unsigned int widthSegments,
    const unsigned int heightSegments
) : width(width), height(height), widthSegments(widthSegments), heightSegments(heightSegments), 
    Mesh(this->getVertices(width, height, widthSegments, heightSegments), this->getIndices(width, height, widthSegments, heightSegments))
{
    spdlog::info("Quad constructor");
}

Quad::~Quad()
{
    spdlog::info("Quad destructor");
}

float Quad::getWidth() const {
    return width;
}

float Quad::getHeight() const {
    return height;
}

unsigned int Quad::getWidthSegments() const {
    return widthSegments;
}

unsigned int Quad::getHeightSegments() const {
    return heightSegments;
}

void Quad::setWidth(float width) {
    this->width = width;
}

void Quad::setHeight(float height) {
    this->height = height;
}

void Quad::setWidthSegments(unsigned int widthSegments) {
    this->widthSegments = widthSegments;
}

void Quad::setHeightSegments(unsigned int heightSegments) {
    this->heightSegments = heightSegments;
}

std::vector<Vertex> Quad::getVertices(
    const float width,
    const float height,
    const unsigned int widthSegments,
    const unsigned int heightSegments
) const
{
    std::vector<Vertex> vertices;

    const float dx = 1.0f / widthSegments;
    const float dy = 1.0f / heightSegments;

    const unsigned int vertexCols = static_cast<unsigned int>(width * widthSegments);
    const unsigned int vertexRows = static_cast<unsigned int>(height * heightSegments);

    for (unsigned int y = 0; y <= vertexRows; ++y)
    {
        for (unsigned int x = 0; x <= vertexCols; ++x)
        {
            ren::components::meshes::Vertex vertex;
            
            vertex.Position = glm::vec3(
                x * dx - static_cast<float>(width) / 2.0f,
                y * dy - static_cast<float>(height) / 2.0f,
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

std::vector<unsigned int> Quad::getIndices(
    const float width,
    const float height,
    const unsigned int widthSegments,
    const unsigned int heightSegments
) const
{
    std::vector<unsigned int> indices;

    const unsigned int vertexCols = static_cast<unsigned int>(width * widthSegments);
    const unsigned int vertexRows = static_cast<unsigned int>(height * heightSegments);
    unsigned int rowStride = vertexCols + 1;

    for (unsigned int y = 0; y < vertexRows; ++y)
    {
        for (unsigned int x = 0; x < vertexCols; ++x)
        {
            unsigned int bl = y * rowStride + x;
            unsigned int br = bl + 1;
            unsigned int tl = bl + rowStride;
            unsigned int tr = tl + 1;

            indices.push_back(bl);
            indices.push_back(br);
            indices.push_back(tr);

            indices.push_back(bl);
            indices.push_back(tr);
            indices.push_back(tl);
        }
    }

    return indices;
}