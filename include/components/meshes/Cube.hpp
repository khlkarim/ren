#pragma once
#include <components/Mesh.hpp>

namespace ren::components::meshes {

class Cube : public Mesh
{
public:
    Cube(
        const float width = 1,
        const float height = 1,
        const float depth = 1,
        const unsigned int widthSegments = 2,
        const unsigned int heightSegments = 2,
        const unsigned int depthSegments = 2
    );
    virtual ~Cube();

    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;

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

private:
    std::vector<Vertex> getFaceVertices(const glm::vec3& normal) const;
    std::vector<unsigned int> getFaceIndices(const glm::vec3& normal) const;

private:
    float width;
    float height;
    float depth;
    unsigned int widthSegments;
    unsigned int heightSegments;
    unsigned int depthSegments;
};

}