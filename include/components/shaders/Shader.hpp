#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

namespace ren::components::shaders {

class Shader
{
public:
    unsigned int getId() const;
    void setId(unsigned int id);

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
private:
    unsigned int id;
};

}