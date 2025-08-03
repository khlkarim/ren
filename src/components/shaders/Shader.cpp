#include <glad/glad.h>
#include <components/shaders/Shader.hpp>
using ren::components::shaders::Shader;

unsigned int Shader::getId() const
{
    return this->id;
}

void Shader::setId(unsigned int id)
{
    this->id = id;
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

void Shader::setVec3Array(const std::string& name, const std::vector<glm::vec3>& values) const
{
    const int uniformLocation = glGetUniformLocation(this->id, name.c_str());
    glUniform3fv(uniformLocation, static_cast<GLsizei>(values.size()), &values[0][0]);
}
