#pragma once

#include <string>
#include <vector>
#include <optional>

// Forward declaration
struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType : int;

namespace ren::ecs::entities { class Entity; }
namespace ren::ecs::components::shaders 
{ 
    class Shader; 
    struct Texture; 
}
// Forward declaration

namespace ren::assets 
{

class AssetManager
{
public:
    ecs::entities::Entity loadEntity(const std::string& path);
    unsigned int loadCubemap(const std::vector<std::string>& faces);
    unsigned int loadTextureFromImage(const std::string& path, bool gamma = false);
    ecs::components::shaders::Shader loadShader(const std::string& vertexShader, const std::string& fragShader) const;

private:
    std::optional<std::string> readText(const std::string& path) const;
    bool checkCompilerErrors(unsigned int shader, const std::string& type) const;

    // Model Processing
    void processNode(ecs::entities::Entity& entity, 
                     const std::string& directory, 
                     const aiScene* scene, 
                     aiNode* node);

    void processMesh(ecs::entities::Entity& entity, 
                     const std::string& directory, 
                     const aiScene* scene, 
                     aiMesh* mesh);

    std::vector<ecs::components::shaders::Texture> loadMaterialTextures(
        const std::string& directory, 
        const std::string& typeName, 
        aiMaterial* material, 
        aiTextureType type);

private:
    std::vector<ecs::components::shaders::Texture> m_texturesLoaded; // Cache for loaded textures
};

}
