#include "Window.hpp"
#include "AssetManager.hpp"
#include <random>

ren::components::meshes::Mesh generateGridMesh();
void setupScene(ren::Window& window, ren::io::AssetManager& assetManager);

int main() {
    ren::Window window("Voronoi", 1980, 1080);
    ren::io::AssetManager assetManager;

    setupScene(window, assetManager);
    return 0;
}

void setupScene(ren::Window& window, ren::io::AssetManager& assetManager) {
    auto shaderOpt = assetManager.loadShader(
        "assets/shaders/voronoi/voronoi.vert", 
        "assets/shaders/voronoi/voronoi.frag"
    );

    if (!shaderOpt) {
        spdlog::critical("Failed to load shaders");
        exit(-1);
    }

    auto model = std::make_shared<ren::Model>();
    auto mesh = std::make_shared<ren::components::meshes::Mesh>(generateGridMesh());
    auto shader = std::make_shared<ren::components::shaders::Shader>(*shaderOpt);

    mesh->setShader(shader);
    model->addMesh(mesh);

    ren::Scene scene;
    scene.camera.setPosition(glm::vec3(0.0f, 8.0f, 10.0f));
    scene.add(model);

    while (window.isOpen()) {
        shader->setFloat("time", static_cast<float>(glfwGetTime()));
        window.render(scene);
    }
}

ren::components::meshes::Mesh generateGridMesh() {
    constexpr int gridWidth = 50;
    constexpr int gridHeight = 50;
    constexpr float cellSize = 0.8f;
    constexpr float offsetRange = 0.4f; // ±0.4 for offset

    std::vector<ren::components::meshes::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ren::components::shaders::Texture> textures;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> offsetDist(-offsetRange, offsetRange);
    std::uniform_real_distribution<float> heightDist(0.0f, 1.0f);
    std::uniform_real_distribution<float> normalDist(-0.5f, 0.5f);

    for (int y = 0; y <= gridHeight; ++y) {
        for (int x = 0; x <= gridWidth; ++x) {
            ren::components::meshes::Vertex v;
            float offsetX = offsetDist(rng);
            float offsetZ = offsetDist(rng);
            float posX = x * cellSize - (cellSize * gridWidth / 2.0f) + offsetX;
            float posY = heightDist(rng);
            float posZ = y * cellSize - (cellSize * gridHeight / 2.0f) + offsetZ;

            v.Position = glm::vec3(posX, posY, posZ);
            v.Normal = glm::vec3(normalDist(rng), normalDist(rng), normalDist(rng));
            vertices.push_back(v);
        }
    }

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            int row1 = y * (gridWidth + 1);
            int row2 = (y + 1) * (gridWidth + 1);

            indices.push_back(row1 + x);
            indices.push_back(row2 + x);
            indices.push_back(row1 + x + 1);

            indices.push_back(row1 + x + 1);
            indices.push_back(row2 + x);
            indices.push_back(row2 + x + 1);
        }
    }

    return ren::components::meshes::Mesh(vertices, indices, textures);
}
