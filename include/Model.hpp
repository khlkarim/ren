#pragma once

#include <spdlog/spdlog.h>
#include <memory>
#include "stb_image.h"
#include "Transform.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Model
{
public:
    Model();
    ~Model();

    void setShader(const std::shared_ptr<Shader>& shader);
    std::shared_ptr<Shader> getShader();

    bool addMesh(const std::shared_ptr<Mesh>& mesh);
    bool removeMesh(const std::shared_ptr<Mesh>& mesh);
    void render(const glm::mat4& projection, const glm::mat4& view);
    
public: 
    Transform transform;

private:
    std::shared_ptr<Shader> shader;
    std::vector<std::shared_ptr<Mesh>> meshes;
};