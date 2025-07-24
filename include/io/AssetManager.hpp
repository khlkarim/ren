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

namespace ren::io {

class AssetManager
{
public:
    ren::components::shaders::Shader loadShader(const std::string& vertexShader, const std::string& fragShader);

private:
    std::optional<std::string> readText(const std::string& path);
    bool checkCompilerErrors(GLuint shader, const std::string& type) const;
};

}