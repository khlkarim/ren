#pragma once

#include "Mesh.hpp"

class Cube : public Mesh
{
public:
    Cube();

private:
    std::vector<Vertex> getVertices();
    std::vector<unsigned int> getIndices();
    std::vector<Texture> getTextures();
};