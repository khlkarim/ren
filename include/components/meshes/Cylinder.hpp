#pragma once

#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Cylinder : public Mesh
{
public:
    Cylinder();
    virtual ~Cylinder();

    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;

private:
    float radius;
    float height;
    unsigned int segments;
    unsigned int rings;
};

}