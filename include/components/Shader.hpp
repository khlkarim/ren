#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>

std::string read(const std::string& path);

class Shader
{
public:
    Shader(const std::string& vertexShader, const std::string& fragShader);
    
    void use();
    
    void setInt(const std::string& name, const int& value) const;
    void setFloat(const std::string& name, const float& value) const;
    void setBool(const std::string& name, const bool& value) const;
    
private:
    unsigned int id;
};

#endif // SHADER_HPP