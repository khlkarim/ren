#pragma once

#include "ecs/components/Mesh.hpp"

namespace ren::ecs::components::meshes {

class Cylinder : public Mesh
{
public:
    Cylinder(
        const float radius = 1,
        const float height = 1,
        const unsigned int segments = 32,
        const unsigned int stacks = 32
    );
    virtual ~Cylinder();

    float getRadius() const;
    float getHeight() const;
    unsigned int getSegments() const;
    unsigned int getStacks() const;

    void setRadius(float r);
    void setHeight(float h);
    void setSegments(unsigned int s);
    void setStacks(unsigned int s);

    static std::vector<Vertex> getVertices(
        const float radius,
        const float height,
        const unsigned int segments,
        const unsigned int stacks
    );
    static std::vector<unsigned int> getIndices(
        const float radius,
        const float height,
        const unsigned int segments,
        const unsigned int stacks
    );

private: 
    float radius;
    float height;
    unsigned int segments;
    unsigned int stacks;
};

}