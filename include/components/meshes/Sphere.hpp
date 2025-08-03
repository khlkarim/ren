#pragma once

#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Sphere : public Mesh
{
public:
    Sphere(
        const float radius = 1,
        const unsigned int segments = 32,
        const unsigned int rings = 32
    );
    virtual ~Sphere();

    static std::vector<Vertex> getVertices(
        const float radius,
        const unsigned int segments,
        const unsigned int rings
    );
    static std::vector<unsigned int> getIndices(
        const float radius,
        const unsigned int segments,
        const unsigned int rings
    );

private: 
    float radius;
    unsigned int segments;
    unsigned int rings;
};

}