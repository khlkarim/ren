#include "Shader.hpp"

Shader::Shader(const std::string& vertexShader, const std::string& fragShader)
{
    const char* vertexCode = read(vertexShader).c_str();
    const char* fragCode = read(fragShader).c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        spdlog::error("Failed to compile vertex shader: {}", infoLog);
    };
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        spdlog::error("Failed to compile fragment shader: {}", infoLog);
    };

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        spdlog::error("Failed to link shader program: {}", infoLog);
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() 
{
    glUseProgram(this->id);
}

void Shader::setInt(const std::string& name, const int& value) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string& name, const float& value) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform1f(uniformLocation, value);
}

void Shader::setBool(const std::string& name, const bool& value) const
{
    this->setInt(name, static_cast<int>(value));
}

std::string read(const std::string& path) 
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
    catch(std::ifstream::failure e)
    {
        spdlog::error("Failed to read file: {}", path);
    }
    
    return result;
}