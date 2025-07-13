#pragma once 

#include <optional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include "Shader.hpp"
#include "Model.hpp"

class AssetManager
{
public:
    std::optional<Model> loadModel(const std::string& path);
    std::optional<Shader> loadShader(const std::string& vertexShader, const std::string& fragShader);

private:
    std::optional<std::string> readText(const std::string& path);
    bool checkCompilerErrors(GLuint shader, const std::string& type) const;
    
    void processNode(aiNode *node, const aiScene *scene, Model& model, const std::string& directory);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, const std::string& directory);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string& dircetory);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

private:
    std::vector<Texture> textures_loaded;
};