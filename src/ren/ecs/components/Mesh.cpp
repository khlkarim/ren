#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "ecs/components/Mesh.hpp"

namespace ren::ecs::components {

Mesh::Mesh(const std::vector<meshes::Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_vertices(vertices), m_indices(indices) 
{
    initialize();
}

void Mesh::initialize()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    
    // Setup vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 
                 m_vertices.size() * sizeof(meshes::Vertex), 
                 m_vertices.data(), 
                 GL_STATIC_DRAW);
    
    // Setup element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 m_indices.size() * sizeof(unsigned int), 
                 m_indices.data(), 
                 GL_STATIC_DRAW);
    
    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                         sizeof(meshes::Vertex), 
                         reinterpret_cast<GLvoid*>(0));

    // Normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
                         sizeof(meshes::Vertex), 
                         reinterpret_cast<GLvoid*>(offsetof(meshes::Vertex, Normal)));
    
    // Texture coordinates attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 
                         sizeof(meshes::Vertex), 
                         reinterpret_cast<GLvoid*>(offsetof(meshes::Vertex, TexCoords)));
    
    glBindVertexArray(0);
    spdlog::info("Mesh initialized successfully");
}

void Mesh::reinitialize()
{
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 
                m_vertices.size() * sizeof(meshes::Vertex), 
                m_vertices.data(), 
                GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                m_indices.size() * sizeof(unsigned int), 
                m_indices.data(), 
                GL_STATIC_DRAW);

    glBindVertexArray(0);
    spdlog::info("Mesh reinitialized successfully");
}

unsigned int Mesh::getVao() const 
{
    return m_vao;
}

unsigned int Mesh::getVbo() const 
{
    return m_vbo;
}

unsigned int Mesh::getEbo() const 
{
    return m_ebo;
}

const std::vector<unsigned int>& Mesh::getIndices() const 
{
    return m_indices;
}

const std::vector<meshes::Vertex>& Mesh::getVertices() const 
{
    return m_vertices;
}

void Mesh::setIndices(const std::vector<unsigned int>& indices)
{
    m_indices = indices;
    reinitialize();
}

void Mesh::setVertices(const std::vector<meshes::Vertex>& vertices)
{
    m_vertices = vertices;
    reinitialize();
}

std::unique_ptr<Component> Mesh::clone() const 
{
    return std::make_unique<Mesh>(*this);
}

} 