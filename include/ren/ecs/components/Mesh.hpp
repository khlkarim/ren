#pragma once

#include <vector>
#include <ren/ecs/components/Component.hpp>
#include <ren/ecs/components/meshes/Vertex.hpp>

namespace ren::ecs::components
{

class Mesh : public Component
{
public:
    Mesh(
        const std::vector<meshes::Vertex>& vertices, 
        const std::vector<unsigned int>& indices
    );

    unsigned int getVAO() const;
    unsigned int getVBO() const;
    unsigned int getEBO() const;

    void setIndices(const std::vector<unsigned int>& indices);
    void setVertices(const std::vector<meshes::Vertex>& vertices);

    const std::vector<unsigned int>& getIndices() const;
    const std::vector<meshes::Vertex>& getVertices() const;
    
    std::unique_ptr<Component> clone() const override;

private:
    void init();
    void reinit();

private:
    unsigned int VAO, VBO, EBO;
    std::vector<meshes::Vertex> vertices;
    std::vector<unsigned int> indices;
};

}
