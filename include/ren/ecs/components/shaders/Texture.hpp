#pragma once

#include <string>

namespace ren::ecs::components::shaders {

struct Texture
{
    enum class TextureType {
        None = 0,
        Diffuse = 1,
        Specular = 2,
        Ambient = 3,
        Emissive = 4,
        Height = 5,
        Normals = 6,
        Shininess = 7,
        Opacity = 8,
        Displacement = 9,
        Lightmap = 10,
        Reflection = 11,
        BaseColor = 12,
        NormalCamera = 13,
        EmissionColor = 14,
        Metalness = 15,
        DiffuseRoughness = 16,
        AmbientOcclusion = 17,
        Unknown = 18,
        Sheen = 19,
        Clearcoat = 20,
        Transmission = 21,
        Anisotropy = 26,
    };

    unsigned int id;
    TextureType type;
    std::string path;
};

}