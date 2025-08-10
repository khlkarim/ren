#pragma once

#include "ecs/components/Mesh.hpp"

namespace ren::ecs::components::meshes {

class Sphere : public Mesh
{
public:
    Sphere(
        float radius = 1,
        unsigned int segments = 32,
        unsigned int rings = 32
    );
    virtual ~Sphere();
    
    float getRadius() const;
    unsigned int getRings() const;
    unsigned int getSegments() const;
    
    void setRadius(float radius);
    void setRings(unsigned int rings);
    void setSegments(unsigned int segments);


    static std::vector<Vertex> getVertices(
        float radius,
        unsigned int segments,
        unsigned int rings
    );
    static std::vector<unsigned int> getIndices(
        unsigned int segments,
        unsigned int rings
    );

protected:
    virtual void reinitialize() override;

private: 
    float m_radius;
    unsigned int m_segments;
    unsigned int m_rings;
};

}