#include <core/Window.hpp>
#include <components/meshes/Quad.hpp>
#include <assets/AssetManager.hpp>

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif

std::vector<glm::vec3> generateColors(const unsigned int count);
std::vector<glm::vec3> generateControlPoints(const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int count);

std::vector<glm::vec3> interpolate(const std::vector<glm::vec3>& init, const std::vector<glm::vec3>& target, const float p);

int main()
{
    ren::Window window("Voronoi", 1980, 1080);
    ren::Scene scene;

    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader("assets\\shaders\\voronoi\\voronoi.vert", "assets\\shaders\\voronoi\\voronoi.frag");

    ren::Entity plane("plane");
    plane.setComponent<ren::components::Mesh>(ren::components::meshes::Quad(10, 5, 250, 250));
    plane.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {}));

    auto& sceneH = scene.getHierarchy();
    sceneH.add(plane);

    std::vector<glm::vec3> initColors = generateColors(20);
    std::vector<glm::vec3> initPositions = generateControlPoints(10, 10, 20);

    std::vector<glm::vec3> targetColors = generateColors(20);
    std::vector<glm::vec3> targetPositions = generateControlPoints(10, 10, 20);
    
    float lastT = static_cast<float>(glfwGetTime());
    while(window.isOpen())
    {
        float currT = static_cast<float>(glfwGetTime());
        float dt = currT - lastT;
        
        auto& mr = sceneH.getComponent<ren::components::MeshRenderer>("plane").value().get();
        auto& s = mr.getShader();
        
        s.setVec3Array("vertexColors", interpolate(initColors, targetColors, dt/5.0f));
        s.setVec3Array("vertexPositions", interpolate(initPositions, targetPositions, dt/5.0f));

        if(dt > 5.0f)
        {
            lastT = currT;

            initColors = targetColors;
            initPositions = targetPositions;
            
            targetColors = generateColors(20);
            targetPositions = generateControlPoints(10, 10, 20);
        }

        window.render(scene);
    }

    return 0;
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