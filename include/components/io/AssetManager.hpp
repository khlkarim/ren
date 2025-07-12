#pragma once 

#include <optional>
#include "Shader.hpp"
#include "Model.hpp"

class AssetManager
{
public:
    std::optional<Model> loadModel(const std::string& path) {}
    std::optional<Shader> loadShader(const std::string& vertexShader, const std::string& fragShader);

private:
    std::optional<std::string> readText(const std::string& path);
    bool checkCompilerErrors(GLuint shader, const std::string& type) const;

};