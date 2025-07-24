#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Capsule : public Mesh
{
public:
    Capsule();
    virtual ~Capsule();

    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;
};

}