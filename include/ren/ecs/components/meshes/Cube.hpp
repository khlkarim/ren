#pragma once

#include <ren/ecs/components/Mesh.hpp>

namespace ren::ecs::components::meshes 
{

class Cube : public Mesh
{
public:
    Cube(
        const float width = 1,
        const float height = 1,
        const float depth = 1,
        const unsigned int widthSegments = 1,
        const unsigned int heightSegments = 1,
        const unsigned int depthSegments = 1
    );
    virtual ~Cube();

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

    static std::vector<Vertex> getVertices(
        const float width,
        const float height,
        const float depth,
        const unsigned int widthSegments,
        const unsigned int heightSegments,
        const unsigned int depthSegments
    );
    static std::vector<unsigned int> getIndices(
        const float width,
        const float height,
        const float depth,
        const unsigned int widthSegments,
        const unsigned int heightSegments,
        const unsigned int depthSegments
    );

private:
    static std::vector<Vertex> getFaceVertices(
        const float width,
        const float height,
        const float depth,
        const unsigned int widthSegments,
        const unsigned int heightSegments,
        const unsigned int depthSegments,
        const glm::vec3& normal
    );
    static std::vector<unsigned int> getFaceIndices(
        const float width,
        const float height,
        const float depth,
        const unsigned int widthSegments,
        const unsigned int heightSegments,
        const unsigned int depthSegments,
        const glm::vec3& normal
    );

private:
    float width;
    float height;
    float depth;
    unsigned int widthSegments;
    unsigned int heightSegments;
    unsigned int depthSegments;
};

}