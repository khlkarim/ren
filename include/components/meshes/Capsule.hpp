#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Capsule : public Mesh
{
public:
    Capsule();
    virtual ~Capsule();

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;
};

}