#pragma once

#include "ecs/components/Mesh.hpp"

namespace ren::ecs::components::meshes 
{

class Cube : public Mesh
{
public:
    Cube(
        float width = 1.0f,
        float height = 1.0f,
        float depth = 1.0f,
        unsigned int widthSegments = 1,
        unsigned int heightSegments = 1,
        unsigned int depthSegments = 1
    );
    virtual ~Cube() override;

    float getWidth() const;
    float getHeight() const;
    float getDepth() const;
    unsigned int getWidthSegments() const;
    unsigned int getHeightSegments() const;
    unsigned int getDepthSegments() const;

    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
    void setWidthSegments(unsigned int widthSegments);
    void setHeightSegments(unsigned int heightSegments);
    void setDepthSegments(unsigned int depthSegments);

    // Static mesh generation methods
    static std::vector<Vertex> getVertices(
        float width,
        float height,
        float depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        unsigned int depthSegments
    );

    static std::vector<unsigned int> getIndices(
        float width,
        float height,
        float depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        unsigned int depthSegments
    );

protected:
    virtual void reinitialize() override;

private:
    // Helper methods for mesh generation
    static std::vector<Vertex> getFaceVertices(
        float width,
        float height,
        float depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        unsigned int depthSegments,
        const glm::vec3& normal
    );
    
    static std::vector<unsigned int> getFaceIndices(
        float width,
        float height,
        float depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        unsigned int depthSegments,
        const glm::vec3& normal
    );

private:
    float m_width;
    float m_height;
    float m_depth;
    unsigned int m_widthSegments;
    unsigned int m_heightSegments;
    unsigned int m_depthSegments;
};

}