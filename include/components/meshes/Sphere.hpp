#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Sphere : public Mesh
{
public:
    Sphere(
        const float radius = 1,
        const unsigned int segments = 16,
        const unsigned int rings = 8
    );
    virtual ~Sphere();

    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;

private: 
    float radius;
    unsigned int segments;
    unsigned int rings;
};

}