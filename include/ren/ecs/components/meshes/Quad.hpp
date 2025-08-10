#pragma once

#include "ecs/components/Mesh.hpp"

namespace ren::ecs::components::meshes {

class Quad : public Mesh {
public:
    Quad(
        float width = 1.0f,
        float height = 1.0f,
        unsigned int widthSegments = 1,
        unsigned int heightSegments = 1
    );
    virtual ~Quad() override;
    
    float getWidth() const;
    float getHeight() const;
    unsigned int getWidthSegments() const;
    unsigned int getHeightSegments() const;
    
    void setWidth(float width);
    void setHeight(float height);
    void setWidthSegments(unsigned int widthSegments);
    void setHeightSegments(unsigned int heightSegments);
    
    static std::vector<Vertex> getVertices(
        float width,
        float height,
        unsigned int widthSegments,
        unsigned int heightSegments
    );
    
    static std::vector<unsigned int> getIndices(
        float width,
        float height,
        unsigned int widthSegments,
        unsigned int heightSegments
    );

protected:
    virtual void reinitialize() override;

private:
    float m_width;
    float m_height;
    unsigned int m_widthSegments;
    unsigned int m_heightSegments;
};

} 