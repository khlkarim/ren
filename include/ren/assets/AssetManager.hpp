#pragma once 

#include <vector>
#include <optional>
#include <glad/glad.h>
#include <assimp/scene.h>
#include <ren/ecs/components/shaders/Texture.hpp>

namespace ren::ecs::entities { class Entity; }
namespace ren::ecs::components::shaders { class Shader; }

namespace ren::assets 
{

class AssetManager
{
public:
    ecs::entities::Entity loadEntity(const std::string& path);
    unsigned int loadTextureFromImage(const std::string& path, bool gamma = false);
    ecs::components::shaders::Shader loadShader(const std::string& vertexShader, const std::string& fragShader);

private:
    std::optional<std::string> readText(const std::string& path);
    bool checkCompilerErrors(GLuint shader, const std::string& type) const;

    void processNode(ecs::entities::Entity& entity, const std::string& directory, const aiScene* scene, aiNode* node);
    void processMesh(ecs::entities::Entity& entity, const std::string& directory, const aiScene* scene, aiMesh* mesh);
    std::vector<ecs::components::shaders::Texture> loadMaterialTextures(const std::string& directory, const std::string& typeName, aiMaterial *mat, aiTextureType type);

private:
    std::vector<ecs::components::shaders::Texture> textures_loaded;
};

}