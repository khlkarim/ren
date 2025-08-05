#pragma once

#include <string>

namespace ren::ecs::components::shaders {

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

}