#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

std::string read(const std::string& path);

class Shader
{
public:
    Shader(const std::string& vertexShader, const std::string& fragShader);

    void use() const;

    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setBool(const std::string& name, bool value) const;

    void setVec2(const std::string& name, float x, float y) const;
    void setVec2(const std::string& name, const glm::vec2& v) const;

    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;

    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setVec4(const std::string& name, const glm::vec4& v) const;

    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    void checkCompilerErrors(GLuint shader, const std::string& type) const;
private:
    unsigned int id;
};

#endif // SHADER_HPP