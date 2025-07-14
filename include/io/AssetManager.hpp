#pragma once 

#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <glad/glad.h>
#include "stb_image.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Model.hpp"
#include "Shader.hpp"

namespace ren::io {

class AssetManager
{
public:
    std::optional<Model> loadModel(const std::string& path);
    std::optional<ren::components::shaders::Shader> loadShader(const std::string& vertexShader, const std::string& fragShader);

private:
    std::optional<std::string> readText(const std::string& path);
    bool checkCompilerErrors(GLuint shader, const std::string& type) const;
    
    void processNode(aiNode *node, const aiScene *scene, Model& model, const std::string& directory);
    ren::components::meshes::Mesh processMesh(aiMesh *mesh, const aiScene *scene, const std::string& directory);
    std::vector<ren::components::shaders::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string& dircetory);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

private:
    std::vector<ren::components::shaders::Texture> textures_loaded;
};

}