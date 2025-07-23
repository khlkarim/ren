#include "AssetManager.hpp"
using ren::io::AssetManager;
using namespace ren::components::shaders;

std::optional<Shader> AssetManager::loadShader(const std::string& vertexShader, const std::string& fragShader)
{
    spdlog::info("Loading vertex shader: {}", vertexShader);
    spdlog::info("Loading fragment shader: {}", fragShader);

    std::optional<std::string> vertexCodeStr = this->readText(vertexShader);
    std::optional<std::string> fragCodeStr = this->readText(fragShader);

    if(!vertexCodeStr.has_value() || !fragCodeStr.has_value()) return std::nullopt;

    const char* vertexCode = vertexCodeStr.value().c_str();
    const char* fragCode = fragCodeStr.value().c_str();
    
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    if(this->checkCompilerErrors(vertex, "VERTEX_SHADER"))
    {
        return std::nullopt;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, NULL);
    glCompileShader(fragment);

    if(this->checkCompilerErrors(fragment, "FRAGMENT_SHADER"))
    {
        return std::nullopt;
    }

    Shader shader;
    shader.setId(glCreateProgram());
    glAttachShader(shader.getId(), vertex);
    glAttachShader(shader.getId(), fragment);
    glLinkProgram(shader.getId());

    if(this->checkCompilerErrors(shader.getId(), "PROGRAM"))
    {
        return std::nullopt;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

std::optional<std::string> AssetManager::readText(const std::string& path)
{
    std::string result;
    std::ifstream file;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try 
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        
        result = stream.str();
    }
    catch(const std::ifstream::failure& e)
    {
        spdlog::error("Failed to read file: {} ({})", path, e.what());
        return std::nullopt;
    }
    
    return result;
}

bool AssetManager::checkCompilerErrors(GLuint shader, const std::string& type) const
{
    GLint success;
    GLchar infoLog[1024];
    
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error("Failed to compile {}: {}", type, infoLog);
            return true;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error("Failed to link program: {}", infoLog);
            return true;
        }
    }

    return false;
}