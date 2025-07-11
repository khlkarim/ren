#include "Shader.hpp"

Shader::Shader(const std::string& vertexShader, const std::string& fragShader)
{
    spdlog::info("Loading vertex shader: {}", vertexShader);
    spdlog::info("Loading fragment shader: {}", fragShader);

    std::string vertexCodeStr = read(vertexShader);
    std::string fragCodeStr = read(fragShader);
    const char* vertexCode = vertexCodeStr.c_str();
    const char* fragCode = fragCodeStr.c_str();
    
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    this->checkCompilerErrors(vertex, "VERTEX_SHADER");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, NULL);
    glCompileShader(fragment);

    this->checkCompilerErrors(fragment, "FRAGMENT_SHADER");

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);

    this->checkCompilerErrors(this->id, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(this->id);
}

void Shader::setInt(const std::string& name, int value) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform1f(uniformLocation, value);
}

void Shader::setBool(const std::string& name, bool value) const
{
    this->setInt(name, static_cast<int>(value));
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform2f(uniformLocation, x, y);
}
void Shader::setVec2(const std::string& name, const glm::vec2& v) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform2fv(uniformLocation, 1, &v[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform3f(uniformLocation, x, y, z);
}
void Shader::setVec3(const std::string& name, const glm::vec3& v) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform3fv(uniformLocation, 1, &v[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform4f(uniformLocation, x, y, z, w);
}
void Shader::setVec4(const std::string& name, const glm::vec4& v) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform4fv(uniformLocation, 1, &v[0]);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompilerErrors(GLuint shader, const std::string& type) const
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
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error("Failed to link program: {}", infoLog);
        }
    }
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
    catch(const std::ifstream::failure& e)
    {
        spdlog::error("Failed to read file: {} ({})", path, e.what());
    }
    
    return result;
}