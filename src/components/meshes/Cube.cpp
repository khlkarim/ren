#include <spdlog/spdlog.h>
#include <components/meshes/Cube.hpp>
using ren::components::meshes::Cube;
using ren::components::meshes::Vertex;

Cube::Cube(
    const float width,
    const float height,
    const float depth,
    const unsigned int widthSegments,
    const unsigned int heightSegments,
    const unsigned int depthSegments
) : width(width), height(height), depth(depth),
    widthSegments(widthSegments), heightSegments(heightSegments), depthSegments(depthSegments),
    Mesh(
        this->getVertices(width, height, depth, widthSegments, heightSegments, depthSegments), 
        this->getIndices(width, height, depth, widthSegments, heightSegments, depthSegments)
    )
{
    spdlog::info("Cube constructor");
}

Cube::~Cube()
{
    spdlog::info("Cube destructor");
}

float Cube::getWidth() const {
    return width;
}

float Cube::getHeight() const {
    return height;
}

float Cube::getDepth() const {
    return depth;
}

unsigned int Cube::getWidthSegments() const {
    return widthSegments;
}

unsigned int Cube::getHeightSegments() const {
    return heightSegments;
}

unsigned int Cube::getDepthSegments() const {
    return depthSegments;
}

void Cube::setWidth(float width) {
    this->width = width;
}

void Cube::setHeight(float height) {
    this->height = height;
}

void Cube::setDepth(float depth) {
    this->depth = depth;
}

void Cube::setWidthSegments(unsigned int widthSegments) {
    this->widthSegments = widthSegments;
}

void Cube::setHeightSegments(unsigned int heightSegments) {
    this->heightSegments = heightSegments;
}

void Cube::setDepthSegments(unsigned int depthSegments) {
    this->depthSegments = depthSegments;
}

std::vector<Vertex> Cube::getVertices(
    const float width,
    const float height,
    const float depth,
    const unsigned int widthSegments,
    const unsigned int heightSegments,
    const unsigned int depthSegments
)
{
    std::vector<glm::vec3> normals = {
        { 0.0f,  0.0f,  1.0f }, 
        { 1.0f,  0.0f,  0.0f },  
        { 0.0f,  1.0f,  0.0f }, 
        {-1.0f,  0.0f,  0.0f }, 
        { 0.0f, -1.0f,  0.0f }, 
        { 0.0f,  0.0f, -1.0f }   
    };

    std::vector<Vertex> vertices;

    for(const auto& normal : normals)
    {
        std::vector<Vertex> face = getFaceVertices(width, height, depth, widthSegments, heightSegments, depthSegments, normal);
        vertices.insert(vertices.end(), face.begin(), face.end());
    }

    return vertices;
}

std::vector<unsigned int> Cube::getIndices(
    const float width,
    const float height,
    const float depth,
    const unsigned int widthSegments,
    const unsigned int heightSegments,
    const unsigned int depthSegments
)
{
    std::vector<glm::vec3> normals = {
        { 0.0f,  0.0f,  1.0f }, 
        { 1.0f,  0.0f,  0.0f },  
        { 0.0f,  1.0f,  0.0f }, 
        {-1.0f,  0.0f,  0.0f }, 
        { 0.0f, -1.0f,  0.0f }, 
        { 0.0f,  0.0f, -1.0f }   
    };

    std::vector<unsigned int> indices;
    unsigned int k = 0;

    for(const auto& normal : normals)
    {
        std::vector<unsigned int> faceI = getFaceIndices(width, height, depth, widthSegments, heightSegments, depthSegments, normal);

        for(unsigned int i = 0; i<faceI.size(); i++)
        {
            faceI[i] += k;
        }

        indices.insert(indices.end(), faceI.begin(), faceI.end());

        std::vector<Vertex> faceV = getFaceVertices(width, height, depth, widthSegments, heightSegments, depthSegments, normal);
        k += static_cast<unsigned int>(faceV.size());
    }

    return indices;
}

std::vector<Vertex> Cube::getFaceVertices(
    const float width,
    const float height,
    const float depth,
    const unsigned int widthSegments,
    const unsigned int heightSegments,
    const unsigned int depthSegments,
    const glm::vec3& normal
)
{
    float w;
    float h;
    unsigned int wSegments;
    unsigned int hSegments;

    if(normal == glm::vec3{ 0.0f,  0.0f,  1.0f } || normal == glm::vec3{ 0.0f,  0.0f,  -1.0f })
    {
        w = width;
        h = height;
        wSegments = widthSegments;
        hSegments = heightSegments;
    }
    else if(normal == glm::vec3{ 1.0f, 0.0f, 0.0f } || normal == glm::vec3{ -1.0f, 0.0f, 0.0f })
    {
        w = depth;
        h = height;
        wSegments = depthSegments;
        hSegments = heightSegments;
    }
    else if(normal == glm::vec3{ 0.0f, 1.0f, 0.0f } || normal == glm::vec3{ 0.0f, -1.0f, 0.0f })
    {
        w = width;
        h = depth;
        wSegments = widthSegments;
        hSegments = depthSegments;
    }

    std::vector<Vertex> vertices;

    const float dx = 1.0f / wSegments;
    const float dy = 1.0f / hSegments;

    const unsigned int vertexCols = static_cast<unsigned int>(w * wSegments);
    const unsigned int vertexRows = static_cast<unsigned int>(h * hSegments);

    for (unsigned int y = 0; y <= vertexRows; ++y)
    {
        for (unsigned int x = 0; x <= vertexCols; ++x)
        {
            ren::components::meshes::Vertex vertex;
            
            // Calculate local face position (centered at origin)
            glm::vec3 localPos(
                (static_cast<float>(x) / static_cast<float>(vertexCols) - 0.5f) * w,
                (static_cast<float>(y) / static_cast<float>(vertexRows) - 0.5f) * h,
                0.0f
            );

            // Determine face orientation
            glm::vec3 pos;
            if (normal == glm::vec3{ 0.0f,  0.0f,  1.0f }) 
            { // +Z
                pos = glm::vec3(localPos.x, localPos.y, 0.5f * depth);
            } 
            else if (normal == glm::vec3{ 0.0f,  0.0f,  -1.0f }) 
            { // -Z
                pos = glm::vec3(-localPos.x, localPos.y, -0.5f * depth);
            } 
            else if (normal == glm::vec3{ 1.0f, 0.0f, 0.0f }) 
            { // +X
                pos = glm::vec3(0.5f * width, localPos.y, -localPos.x);
            } 
            else if (normal == glm::vec3{ -1.0f, 0.0f, 0.0f }) 
            { // -X
                pos = glm::vec3(-0.5f * width, localPos.y, localPos.x);
            } 
            else if (normal == glm::vec3{ 0.0f, 1.0f, 0.0f }) 
            { // +Y
                pos = glm::vec3(localPos.x, 0.5f * height, -localPos.y);
            } 
            else if (normal == glm::vec3{ 0.0f, -1.0f, 0.0f }) 
            { // -Y
                pos = glm::vec3(localPos.x, -0.5f * height, localPos.y);
            } 
            else 
            {
                pos = localPos;
            }

            vertex.Position = pos;
            vertex.Normal = normal;
            vertex.TexCoords = glm::vec2(
                static_cast<float>(x) / static_cast<float>(vertexCols),
                static_cast<float>(y) / static_cast<float>(vertexRows)
            );

            vertices.push_back(vertex);
        }
    }

    return vertices;
}

std::vector<unsigned int> Cube::getFaceIndices(
    const float width,
    const float height,
    const float depth,
    const unsigned int widthSegments,
    const unsigned int heightSegments,
    const unsigned int depthSegments,
    const glm::vec3& normal
)
{
    float w;
    float h;
    unsigned int wSegments;
    unsigned int hSegments;

    if(normal == glm::vec3{ 0.0f,  0.0f,  1.0f } || normal == glm::vec3{ 0.0f,  0.0f,  -1.0f })
    {
        w = width;
        h = height;
        wSegments = widthSegments;
        hSegments = heightSegments;
    }
    else if(normal == glm::vec3{ 1.0f, 0.0f, 0.0f } || normal == glm::vec3{ -1.0f, 0.0f, 0.0f })
    {
        w = depth;
        h = height;
        wSegments = depthSegments;
        hSegments = heightSegments;
    }
    else if(normal == glm::vec3{ 0.0f, 1.0f, 0.0f } || normal == glm::vec3{ 0.0f, -1.0f, 0.0f })
    {
        w = width;
        h = depth;
        wSegments = widthSegments;
        hSegments = depthSegments;
    }

    std::vector<unsigned int> indices;

    const unsigned int vertexCols = static_cast<unsigned int>(w * wSegments);
    const unsigned int vertexRows = static_cast<unsigned int>(h * hSegments);
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