#pragma once 

#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <glad/glad.h>
#include <utils/stb_image.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <components/Mesh.hpp>
#include <components/MeshRenderer.hpp>
#include <components/shaders/Shader.hpp>
#include <utils/error_handler.hpp>
#include <core/Entity.hpp>
#include <components/Hierarchy.hpp>
#include <components/Transform.hpp>

namespace ren::io {

class AssetManager
{
public:
    ren::Entity loadEntity(const std::string& path);
    unsigned int loadTextureFromImage(const std::string& path, bool gamma = false);
    ren::components::shaders::Shader loadShader(const std::string& vertexShader, const std::string& fragShader);

private:
    std::optional<std::string> readText(const std::string& path);
    bool checkCompilerErrors(GLuint shader, const std::string& type) const;

    void processNode(Entity& entity, const std::string& directory, const aiScene* scene, aiNode* node);
    void processMesh(Entity& entity, const std::string& directory, const aiScene* scene, aiMesh* mesh);
    std::vector<ren::components::shaders::Texture> loadMaterialTextures(const std::string& directory, const std::string& typeName, aiMaterial *mat, aiTextureType type);

private:
    std::vector<ren::components::shaders::Texture> textures_loaded;
};

}