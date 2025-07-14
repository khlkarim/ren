#pragma once
#include "Mesh.hpp"

namespace ren::components::meshes {

class Cube : public Mesh
{
public:
    Cube();

private:
    std::vector<Vertex> getVertices();
    std::vector<unsigned int> getIndices();
    std::vector<ren::components::shaders::Texture> getTextures();
};

}