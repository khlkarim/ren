#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Cube : public Mesh
{
public:
    Cube();
    virtual ~Cube();

    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;
};

}