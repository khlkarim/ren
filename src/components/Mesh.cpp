#include <components/Mesh.hpp>

using ren::components::Mesh;
using ren::components::Component;
using ren::components::meshes::Vertex;

Mesh::Mesh(
    const std::vector<Vertex>& vertices, 
    const std::vector<unsigned int>& indices
) {
    this->vertices = vertices;
    this->indices = indices;

    this->init();
}

void Mesh::init()
{
    spdlog::info("initializing mesh");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    spdlog::info("vertices initialized");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    spdlog::info("indices initialized");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Normal)));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, TexCoords)));
    
    glBindVertexArray(0);
}

void Mesh::reinit()
{
    spdlog::info("reinitializing mesh data");

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

unsigned int Mesh::getVAO() const {
    return VAO;
}

unsigned int Mesh::getVBO() const {
    return VBO;
}

unsigned int Mesh::getEBO() const {
    return EBO;
}

const std::vector<unsigned int>& Mesh::getIndices() const {
    return indices;
}

const std::vector<Vertex>& Mesh::getVertices() const {
    return vertices;
}

void Mesh::setIndices(const std::vector<unsigned int>& indices)
{
    this->indices = indices;
    this->reinit();
}

void Mesh::setVertices(const std::vector<meshes::Vertex>& vertices)
{
    this->vertices = vertices;
    this->reinit();
}

std::unique_ptr<Component> Mesh::clone() const {
    return std::make_unique<Mesh>(*this);
}