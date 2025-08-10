#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"

namespace {
    // Function prototypes
    std::vector<glm::vec3> GenerateRandomColors(size_t count);
    std::vector<glm::vec3> GenerateRandomControlPoints(size_t gridWidth, size_t gridHeight, size_t count);
    std::vector<glm::vec3> Interpolate(const std::vector<glm::vec3>& initial, const std::vector<glm::vec3>& target, float factor);
    
    constexpr size_t kNumPoints = 20;
    constexpr size_t kGridWidth = 10;
    constexpr size_t kGridHeight = 10;
    constexpr float kAnimationDuration = 5.0f;
    constexpr int kWindowWidth = 1980;
    constexpr int kWindowHeight = 1080;
    constexpr int kQuadWidth = 10;
    constexpr int kQuadHeight = 5;
    constexpr int kQuadSubdivX = 250;
    constexpr int kQuadSubdivY = 250;
}

int main()
{
    // Create window and scene
    ren::core::Window window("Voronoi", kWindowWidth, kWindowHeight);
    ren::core::Scene scene;

    // Load shader
    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets\\shaders\\voronoi\\voronoi.vert", 
        "assets\\shaders\\voronoi\\voronoi.frag"
    );

    // Create plane entity
    ren::ecs::entities::Entity plane("plane");
    auto& componentManager = plane.getComponentManager();
    componentManager.set(ren::ecs::components::MeshRenderer(shader, {}));
    componentManager.set(ren::ecs::components::meshes::Quad(
        kQuadWidth, kQuadHeight, kQuadSubdivX, kQuadSubdivY));

    // Add entity to scene
    auto& entityManager = scene.getEntityManager();
    entityManager.add(plane);

    // Generate initial and target data
    std::vector<glm::vec3> initialColors = GenerateRandomColors(kNumPoints);
    std::vector<glm::vec3> initialPositions = GenerateRandomControlPoints(kGridWidth, kGridHeight, kNumPoints);
    std::vector<glm::vec3> targetColors = GenerateRandomColors(kNumPoints);
    std::vector<glm::vec3> targetPositions = GenerateRandomControlPoints(kGridWidth, kGridHeight, kNumPoints);
    
    // Setup renderer
    ren::renderer::Renderer renderer;
    renderer.setRenderTarget(window.getGlfwWindow());

    // Main loop
    float lastTime = static_cast<float>(glfwGetTime());
    while(window.isOpen())
    {
        // Calculate time delta
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        
        // Update shader parameters
        auto& meshRenderer = entityManager.getComponent<ren::ecs::components::MeshRenderer>("plane").value().get();
        auto& shader = meshRenderer.getShader();
        
        float interpolationFactor = deltaTime / kAnimationDuration;
        shader.setVec3Array("vertexColors", Interpolate(initialColors, targetColors, interpolationFactor));
        shader.setVec3Array("vertexPositions", Interpolate(initialPositions, targetPositions, interpolationFactor));

        // Start next animation cycle
        if(deltaTime > kAnimationDuration)
        {
            lastTime = currentTime;

            initialColors = targetColors;
            initialPositions = targetPositions;
            
            targetColors = GenerateRandomColors(kNumPoints);
            targetPositions = GenerateRandomControlPoints(kGridWidth, kGridHeight, kNumPoints);
        }

        // Render the scene
        renderer.render(scene);
    }

    return 0;
}

namespace {
    std::vector<glm::vec3> GenerateRandomColors(size_t count)
    {
        std::vector<glm::vec3> colors;
        colors.reserve(count);

        for (size_t i = 0; i < count; ++i) {
            float r = static_cast<float>(rand()) / RAND_MAX;
            float g = static_cast<float>(rand()) / RAND_MAX;
            float b = static_cast<float>(rand()) / RAND_MAX;
            colors.emplace_back(r, g, b);
        }
        
        return colors;
    }

    std::vector<glm::vec3> GenerateRandomControlPoints(size_t gridWidth, size_t gridHeight, size_t count)
    {
        std::vector<glm::vec3> controlPoints;
        controlPoints.reserve(count);

        for (size_t i = 0; i < count; ++i) {
            float x = static_cast<float>(rand()) / RAND_MAX * gridWidth - gridWidth / 2.0f;
            float y = static_cast<float>(rand()) / RAND_MAX * gridHeight - gridHeight / 2.0f;
            float z = 0.0f;
            controlPoints.emplace_back(x, y, z);
        }

        return controlPoints;
    }

    std::vector<glm::vec3> Interpolate(const std::vector<glm::vec3>& initial, const std::vector<glm::vec3>& target, float factor)
    {
        const float clampedFactor = std::clamp(factor, 0.0f, 1.0f);
        std::vector<glm::vec3> result;
        result.reserve(initial.size());

        for(size_t i = 0; i < initial.size(); i++)
        {
            result.emplace_back((1.0f - clampedFactor) * initial[i] + clampedFactor * target[i]);
        }

        return result;
    }
}