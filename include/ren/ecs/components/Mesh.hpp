#pragma once

#include <memory>
#include <vector>
#include "ecs/components/Component.hpp"
#include "ecs/components/meshes/Vertex.hpp"

namespace ren::ecs::components {

class Mesh : public Component {
public:
    Mesh(const std::vector<meshes::Vertex>& vertices, 
         const std::vector<unsigned int>& indices);
    virtual ~Mesh() = default;

    unsigned int getVao() const;
    unsigned int getVbo() const;
    unsigned int getEbo() const;
    
    const std::vector<unsigned int>& getIndices() const;
    const std::vector<meshes::Vertex>& getVertices() const;
    
    void setIndices(const std::vector<unsigned int>& indices);
    void setVertices(const std::vector<meshes::Vertex>& vertices);
    
    std::unique_ptr<Component> clone() const override;

protected:
    void initialize();
    virtual void reinitialize();

protected:
    // Mesh data
    std::vector<meshes::Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

private:
    // GPU buffer objects
    unsigned int m_vao{0};
    unsigned int m_vbo{0};
    unsigned int m_ebo{0};

};

}
