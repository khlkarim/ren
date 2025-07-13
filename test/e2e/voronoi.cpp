#include "Window.hpp"
#include "AssetManager.hpp"

Mesh getGridMesh();

int main() {
    Window window("Voronoi", 1980, 1080);

    AssetManager assetManager;
    std::optional<Shader> shaderOpt = assetManager.loadShader(
        "assets\\shaders\\voronoi\\voronoi.vert", 
        "assets\\shaders\\voronoi\\voronoi.frag"
    );

    if(shaderOpt.has_value())
    {
        std::shared_ptr<Shader> shader(new Shader(shaderOpt.value()));

        std::shared_ptr<Mesh> mesh(new Mesh(getGridMesh()));
        mesh->setShader(shader);

        std::shared_ptr<Model> model(new Model());
        model->addMesh(mesh);
        
        Scene scene;
        scene.camera.setPosition(glm::vec3(0.0f, 8.0f, 10.0f));
        scene.add(model);
    
        while(window.isOpen())
        {
            shader->setFloat("time", static_cast<float>(glfwGetTime()));
            window.render(scene);
        }
    }

    return 0;
}

Mesh getGridMesh()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    const int gridWidth = 50;
    const int gridHeight = 50;
    const float cellSize = 0.8f;

    for (int y = 0; y <= gridHeight; ++y) {
        for (int x = 0; x <= gridWidth; ++x) {
            Vertex v;
            float offsetX = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.8f;
            float offsetY = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.8f;
            v.Position = glm::vec3(
                x * cellSize - cellSize*gridWidth / 2 + offsetX,
                (static_cast<float>(rand()) / RAND_MAX),
                y * cellSize - cellSize*gridHeight / 2 + offsetY
            );
            v.Normal = glm::vec3(
                (static_cast<float>(rand()) / RAND_MAX - 0.5f),
                (static_cast<float>(rand()) / RAND_MAX - 0.5f),
                (static_cast<float>(rand()) / RAND_MAX - 0.5f)
            );
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

    return Mesh(vertices, indices, textures);
}