#include <core/Window.hpp>
#include <components/meshes/Cube.hpp>
#include <io/AssetManager.hpp>

ren::components::Mesh generateMesh();
std::vector<ren::components::meshes::Vertex> generateVertices(const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int subdivisionsPerUnit);
std::vector<unsigned int> generateIndices(const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int subdivisionsPerUnit);

std::vector<glm::vec3> generateColors(const unsigned int count);
std::vector<glm::vec3> generateControlPoints(const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int count);

std::vector<glm::vec3> interpolate(const std::vector<glm::vec3>& init, const std::vector<glm::vec3>& target, const float p);

int main()
{
    ren::Window window("Voronoi", 1980, 1080);
    ren::Scene scene;

    ren::io::AssetManager assetManager;
    auto shader = assetManager.loadShader("assets\\shaders\\voronoi\\voronoi.vert", "assets\\shaders\\voronoi\\voronoi.frag");

    ren::Entity plane("plane");
    plane.setComponent<ren::components::Mesh>(generateMesh());
    plane.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {}));

    auto& sceneH = scene.getHierarchy();
    sceneH.add(plane);

    std::vector<glm::vec3> initColors = generateColors(10);
    std::vector<glm::vec3> initPositions = generateControlPoints(10, 10, 10);

    std::vector<glm::vec3> targetColors = generateColors(10);
    std::vector<glm::vec3> targetPositions = generateControlPoints(10, 10, 10);
    
    float lastT = static_cast<float>(glfwGetTime());
    while(window.isOpen())
    {
        float currT = static_cast<float>(glfwGetTime());
        float dt = currT - lastT;
        
        auto& mr = sceneH.getComponent<ren::components::MeshRenderer>("plane");
        auto& s = mr.getShader();
        
        s.setVec3Array("vertexColors", interpolate(initColors, targetColors, dt/3.0f));
        s.setVec3Array("vertexPositions", interpolate(initPositions, targetPositions, dt/3.0f));

        if(dt > 3.0f)
        {
            lastT = currT;

            initColors = targetColors;
            initPositions = targetPositions;
            
            targetColors = generateColors(10);
            targetPositions = generateControlPoints(10, 10, 10);
        }

        window.render(scene);
    }

    return 0;
}

ren::components::Mesh generateMesh()
{
    const unsigned int gridWidth = 7;
    const unsigned int gridHeight = 4;
    const unsigned int subdivisionsPerUnit = 500;
    
    return ren::components::Mesh(generateVertices(gridWidth, gridHeight, subdivisionsPerUnit), generateIndices(gridWidth, gridHeight, subdivisionsPerUnit));
}

std::vector<ren::components::meshes::Vertex> generateVertices(
    const unsigned int gridWidth, 
    const unsigned int gridHeight, 
    const unsigned int subdivisionsPerUnit)
{
    std::vector<ren::components::meshes::Vertex> vertices;

    const float dx = 1.0f / subdivisionsPerUnit;
    const float dy = 1.0f / subdivisionsPerUnit;

    const unsigned int vertexCols = gridWidth * subdivisionsPerUnit;
    const unsigned int vertexRows = gridHeight * subdivisionsPerUnit;

    for (unsigned int y = 0; y <= vertexRows; ++y)
    {
        for (unsigned int x = 0; x <= vertexCols; ++x)
        {
            ren::components::meshes::Vertex vertex;
            vertex.Position = glm::vec3(
                x * dx - static_cast<float>(gridWidth) / 2.0f,
                y * dy - static_cast<float>(gridHeight) / 2.0f,
                0.0f
            );
            vertices.push_back(vertex);
        }
    }

    return vertices;
}

std::vector<unsigned int> generateIndices(
    const unsigned int gridWidth, 
    const unsigned int gridHeight,
    const unsigned int subdivisionsPerUnit)
{
    std::vector<unsigned int> indices;

    const unsigned int vertexCols = gridWidth * subdivisionsPerUnit;
    const unsigned int vertexRows = gridHeight * subdivisionsPerUnit;
    unsigned int rowStride = vertexCols + 1;

    for (unsigned int y = 0; y < vertexRows; ++y)
    {
        for (unsigned int x = 0; x < vertexCols; ++x)
        {
            unsigned int bl = y * rowStride + x;
            unsigned int br = bl + 1;
            unsigned int tl = bl + rowStride;
            unsigned int tr = tl + 1;

            // Triangle 1
            indices.push_back(bl);
            indices.push_back(br);
            indices.push_back(tr);

            // Triangle 2
            indices.push_back(bl);
            indices.push_back(tr);
            indices.push_back(tl);
        }
    }

    return indices;
}

std::vector<glm::vec3> generateColors(const unsigned int count)
{
    std::vector<glm::vec3> colors;
    colors.reserve(count);

    for (unsigned int i = 0; i < count; ++i) {
        float r = static_cast<float>(rand()) / RAND_MAX;
        float g = static_cast<float>(rand()) / RAND_MAX;
        float b = static_cast<float>(rand()) / RAND_MAX;
        colors.emplace_back(r, g, b);
    }
    
    return colors;
}

std::vector<glm::vec3> generateControlPoints(const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int count)
{
    std::vector<glm::vec3> controlPoints;
    controlPoints.reserve(count);

    for (unsigned int i = 0; i < count; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * gridWidth - gridWidth / 2.0f;
        float y = static_cast<float>(rand()) / RAND_MAX * gridHeight - gridHeight / 2.0f;
        float z = 0.0f;
        controlPoints.emplace_back(x, y, z);
    }

    return controlPoints;
}

std::vector<glm::vec3> interpolate(const std::vector<glm::vec3>& init, const std::vector<glm::vec3>& target, const float p)
{
    const float t = glm::min<float>(1.0f, glm::max<float>(0.0f, p));

    std::vector<glm::vec3> res;
    res.reserve(init.size());

    for(unsigned int i = 0; i<init.size(); i++)
    {
        res.emplace_back((1-t) * init[i] + t * target[i]);
    }

    return res;
}