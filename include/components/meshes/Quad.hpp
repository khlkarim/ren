#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Quad : public Mesh
{
public:
    Quad();
    virtual ~Quad();

    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;
};

}