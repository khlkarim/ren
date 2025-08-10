#pragma once

#include <vector>
#include "ecs/components/Mesh.hpp"

namespace ren::ecs::components::meshes {

class Cylinder : public Mesh {
public:
    Cylinder(
        float radius = 1.0f,
        float height = 1.0f,
        unsigned int segments = 32,
        unsigned int stacks = 32
    );
    virtual ~Cylinder() override;

    float getRadius() const;
    float getHeight() const;
    unsigned int getSegments() const;
    unsigned int getStacks() const;

    void setRadius(float radius);
    void setHeight(float height);
    void setSegments(unsigned int segments);
    void setStacks(unsigned int stacks);

    // Static mesh generation methods
    static std::vector<Vertex> getVertices(
        float radius,
        float height,
        unsigned int segments,
        unsigned int stacks
    );
    
    static std::vector<unsigned int> getIndices(
        unsigned int segments,
        unsigned int stacks
    );

protected:
    virtual void reinitialize() override;

private:
    float m_radius;
    float m_height;
    unsigned int m_segments;
    unsigned int m_stacks;
};

} // namespace ren::ecs::components::meshes