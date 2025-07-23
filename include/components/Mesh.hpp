#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <components/Component.hpp>
#include <components/meshes/Vertex.hpp>

namespace ren::components
{

class Mesh : public Component
{
public:
    Mesh(
        const std::vector<meshes::Vertex>& vertices, 
        const std::vector<unsigned int>& indices
    );

private:
    void init();

public:
    unsigned int VAO, VBO, EBO;
    std::vector<meshes::Vertex> vertices;
    std::vector<unsigned int> indices;
};

}
