#include <spdlog/spdlog.h>
#include "ecs/components/meshes/Cube.hpp"

namespace ren::ecs::components::meshes {

Cube::Cube(
    float width,
    float height,
    float depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments
) : Mesh(
        getVertices(width, height, depth, widthSegments, heightSegments, depthSegments), 
        getIndices(width, height, depth, widthSegments, heightSegments, depthSegments)
    ),
    m_width(width), 
    m_height(height), 
    m_depth(depth),
    m_widthSegments(widthSegments), 
    m_heightSegments(heightSegments), 
    m_depthSegments(depthSegments)
{
    spdlog::info("Cube constructor");
}

Cube::~Cube()
{
    spdlog::info("Cube destructor");
}

float Cube::getWidth() const {
    return m_width;
}

float Cube::getHeight() const {
    return m_height;
}

float Cube::getDepth() const {
    return m_depth;
}

unsigned int Cube::getWidthSegments() const {
    return m_widthSegments;
}

unsigned int Cube::getHeightSegments() const {
    return m_heightSegments;
}

unsigned int Cube::getDepthSegments() const {
    return m_depthSegments;
}

void Cube::setWidth(float width) {
    m_width = width;
    reinitialize();
}

void Cube::setHeight(float height) {
    m_height = height;
    reinitialize();
}

void Cube::setDepth(float depth) {
    m_depth = depth;
    reinitialize();
}

void Cube::setWidthSegments(unsigned int widthSegments) {
    m_widthSegments = widthSegments;
    reinitialize();
}

void Cube::setHeightSegments(unsigned int heightSegments) {
    m_heightSegments = heightSegments;
    reinitialize();
}

void Cube::setDepthSegments(unsigned int depthSegments) {
    m_depthSegments = depthSegments;
    reinitialize();
}

void Cube::reinitialize() {
    m_vertices = getVertices(m_width, m_height, m_depth, m_widthSegments, m_heightSegments, m_depthSegments);
    m_indices = getIndices(m_width, m_height, m_depth, m_widthSegments, m_heightSegments, m_depthSegments);
    Mesh::reinitialize();
}

std::vector<Vertex> Cube::getVertices(
    float width,
    float height,
    float depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments
) {
    static const std::vector<glm::vec3> FACE_NORMALS = {
        { 0.0f,  0.0f,  1.0f },  // Front (+Z)
        { 1.0f,  0.0f,  0.0f },  // Right (+X)
        { 0.0f,  1.0f,  0.0f },  // Top (+Y)
        {-1.0f,  0.0f,  0.0f },  // Left (-X)
        { 0.0f, -1.0f,  0.0f },  // Bottom (-Y)
        { 0.0f,  0.0f, -1.0f }   // Back (-Z)
    };

    std::vector<Vertex> vertices;
    vertices.reserve(FACE_NORMALS.size() * (widthSegments + 1) * (heightSegments + 1));

    for (const auto& normal : FACE_NORMALS) {
        std::vector<Vertex> faceVertices = getFaceVertices(
            width, height, depth, 
            widthSegments, heightSegments, depthSegments, 
            normal);
        vertices.insert(vertices.end(), faceVertices.begin(), faceVertices.end());
    }

    return vertices;
}

std::vector<unsigned int> Cube::getIndices(
    float width,
    float height,
    float depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments
) {
    static const std::vector<glm::vec3> FACE_NORMALS = {
        { 0.0f,  0.0f,  1.0f },  // Front (+Z)
        { 1.0f,  0.0f,  0.0f },  // Right (+X)
        { 0.0f,  1.0f,  0.0f },  // Top (+Y)
        {-1.0f,  0.0f,  0.0f },  // Left (-X)
        { 0.0f, -1.0f,  0.0f },  // Bottom (-Y)
        { 0.0f,  0.0f, -1.0f }   // Back (-Z)
    };

    std::vector<unsigned int> indices;
    unsigned int vertexOffset = 0;

    for (const auto& normal : FACE_NORMALS) {
        // Get indices for this face
        std::vector<unsigned int> faceIndices = getFaceIndices(
            width, height, depth, 
            widthSegments, heightSegments, depthSegments, 
            normal);
        
        // Offset indices by current vertex count
        for (unsigned int& index : faceIndices) {
            index += vertexOffset;
        }
        
        // Add to final indices
        indices.insert(indices.end(), faceIndices.begin(), faceIndices.end());
        
        // Increment vertex offset by the number of vertices in this face
        std::vector<Vertex> faceVertices = getFaceVertices(
            width, height, depth, 
            widthSegments, heightSegments, depthSegments, 
            normal);
        vertexOffset += static_cast<unsigned int>(faceVertices.size());
    }

    return indices;
}

std::vector<Vertex> Cube::getFaceVertices(
    float width,
    float height,
    float depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments,
    const glm::vec3& normal
) {
    // Determine face dimensions based on normal direction
    float faceWidth;
    float faceHeight;
    unsigned int faceWidthSegments;
    unsigned int faceHeightSegments;
    
    if (normal.z != 0.0f) {  // Front/Back faces
        faceWidth = width;
        faceHeight = height;
        faceWidthSegments = widthSegments;
        faceHeightSegments = heightSegments;
    }
    else if (normal.x != 0.0f) {  // Left/Right faces
        faceWidth = depth;
        faceHeight = height;
        faceWidthSegments = depthSegments;
        faceHeightSegments = heightSegments;
    }
    else {  // Top/Bottom faces
        faceWidth = width;
        faceHeight = depth;
        faceWidthSegments = widthSegments;
        faceHeightSegments = depthSegments;
    }

    const unsigned int vertexCols = faceWidthSegments + 1;
    const unsigned int vertexRows = faceHeightSegments + 1;
    std::vector<Vertex> vertices;
    vertices.reserve(vertexCols * vertexRows);

    for (unsigned int row = 0; row < vertexRows; ++row) {
        for (unsigned int col = 0; col < vertexCols; ++col) {
            Vertex vertex;
            
            // Calculate UV coordinates (0 to 1)
            float u = static_cast<float>(col) / static_cast<float>(faceWidthSegments);
            float v = static_cast<float>(row) / static_cast<float>(faceHeightSegments);
            
            // Calculate local face position (centered at origin, -0.5 to 0.5)
            float localX = (u - 0.5f) * faceWidth;
            float localY = (v - 0.5f) * faceHeight;
            
            // Transform to 3D space based on face normal
            if (normal == glm::vec3{ 0.0f, 0.0f, 1.0f }) {        // Front (+Z)
                vertex.Position = glm::vec3(localX, localY, 0.5f * depth);
            } 
            else if (normal == glm::vec3{ 0.0f, 0.0f, -1.0f }) {  // Back (-Z)
                vertex.Position = glm::vec3(-localX, localY, -0.5f * depth);
            } 
            else if (normal == glm::vec3{ 1.0f, 0.0f, 0.0f }) {   // Right (+X)
                vertex.Position = glm::vec3(0.5f * width, localY, -localX);
            } 
            else if (normal == glm::vec3{ -1.0f, 0.0f, 0.0f }) {  // Left (-X)
                vertex.Position = glm::vec3(-0.5f * width, localY, localX);
            } 
            else if (normal == glm::vec3{ 0.0f, 1.0f, 0.0f }) {   // Top (+Y)
                vertex.Position = glm::vec3(localX, 0.5f * height, -localY);
            } 
            else if (normal == glm::vec3{ 0.0f, -1.0f, 0.0f }) {  // Bottom (-Y)
                vertex.Position = glm::vec3(localX, -0.5f * height, localY);
            }

            vertex.Normal = normal;
            vertex.TexCoords = glm::vec2(u, v);
            
            vertices.push_back(vertex);
        }
    }

    return vertices;
}

std::vector<unsigned int> Cube::getFaceIndices(
    float width,
    float height,
    float depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments,
    const glm::vec3& normal
) {
    // Determine face segment counts based on normal direction
    unsigned int faceWidthSegments;
    unsigned int faceHeightSegments;
    
    if (normal.z != 0.0f) {  // Front/Back faces
        faceWidthSegments = widthSegments;
        faceHeightSegments = heightSegments;
    }
    else if (normal.x != 0.0f) {  // Left/Right faces
        faceWidthSegments = depthSegments;
        faceHeightSegments = heightSegments;
    }
    else {  // Top/Bottom faces
        faceWidthSegments = widthSegments;
        faceHeightSegments = depthSegments;
    }

    std::vector<unsigned int> indices;
    indices.reserve(faceWidthSegments * faceHeightSegments * 6);  // 6 indices per grid cell (2 triangles)

    const unsigned int rowStride = faceWidthSegments + 1;

    for (unsigned int row = 0; row < faceHeightSegments; ++row) {
        for (unsigned int col = 0; col < faceWidthSegments; ++col) {
            unsigned int bottomLeft = row * rowStride + col;
            unsigned int bottomRight = bottomLeft + 1;
            unsigned int topLeft = bottomLeft + rowStride;
            unsigned int topRight = topLeft + 1;

            // First triangle (bottom-left, bottom-right, top-right)
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);

            // Second triangle (bottom-left, top-right, top-left)
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topLeft);
        }
    }

    return indices;
}

} 
