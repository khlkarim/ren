#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"


namespace ren {

class Model
{
public:
    Model();
    ~Model();

    void setShader(const std::shared_ptr<ren::components::shaders::Shader>& shader);
    std::shared_ptr<ren::components::shaders::Shader> getShader();

    bool addMesh(const std::shared_ptr<ren::components::meshes::Mesh>& mesh);
    bool removeMesh(const std::shared_ptr<ren::components::meshes::Mesh>& mesh);
    void render(const glm::mat4& projection, const glm::mat4& view);
    
public: 
    ren::components::Transform transform;

private:
    std::shared_ptr<ren::components::shaders::Shader> shader;
    std::vector<std::shared_ptr<ren::components::meshes::Mesh>> meshes;
};

}