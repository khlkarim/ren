#pragma once

#include <string>

namespace ren::components::shaders {

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

}