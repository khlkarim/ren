#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Quad : public Mesh
{
public:
    Quad();
    virtual ~Quad();

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;
};

}