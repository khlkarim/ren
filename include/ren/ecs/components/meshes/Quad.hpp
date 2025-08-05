#pragma once

#include <ren/ecs/components/Mesh.hpp>

namespace ren::ecs::components::meshes {

class Quad : public Mesh
{
public:
    Quad(
        const float width = 1,
        const float height = 1,
        const unsigned int widthSegments = 1,
        const unsigned int heightSegments = 1
    );
    virtual ~Quad();
    
    float getWidth() const;
    float getHeight() const;
    unsigned int getWidthSegments() const;
    unsigned int getHeightSegments() const;
    
    void setWidth(float width);
    void setHeight(float height);
    void setWidthSegments(unsigned int widthSegments);
    void setHeightSegments(unsigned int heightSegments);
    
    static std::vector<Vertex> getVertices(
        const float width,
        const float height,
        const unsigned int widthSegments,
        const unsigned int heightSegments
    );
    static std::vector<unsigned int> getIndices(
        const float width,
        const float height,
        const unsigned int widthSegments,
        const unsigned int heightSegments
    );

private:
    float width;
    float height;
    unsigned int widthSegments;
    unsigned int heightSegments;
};

}