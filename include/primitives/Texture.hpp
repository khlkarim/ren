#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

#endif // TEXTURE_HPP