#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Sphere : public Mesh
{
public:
    Sphere();
    virtual ~Sphere();

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;
};

}