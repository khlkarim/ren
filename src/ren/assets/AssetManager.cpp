#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "assets/AssetManager.hpp"

#include "utils/stb_image.h"
#include "utils/error_handler.hpp"

#include "ecs/entities/Entity.hpp"
#include "ecs/components/Mesh.hpp"
#include "ecs/components/Hierarchy.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/MeshRenderer.hpp"
#include "ecs/components/shaders/Shader.hpp"


namespace ren::assets {

using ecs::entities::Entity;
using ecs::components::Mesh;
using ecs::components::MeshRenderer;
using ecs::components::Transform;
using ecs::components::Hierarchy;
using ecs::components::meshes::Vertex;
using ecs::components::shaders::Shader;
using ecs::components::shaders::Texture;

std::optional<std::string> AssetManager::readText(const std::string& path) const 
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str();
    } catch(const std::ifstream::failure& e) {
        spdlog::error("Failed to read file: {} ({})", path, e.what());
        return std::nullopt;
    }
}

bool AssetManager::checkCompilerErrors(unsigned int shader, const std::string& type) const {
    GLint success;
    GLchar infoLog[1024];
    
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            spdlog::error("Failed to compile {}: {}", type, infoLog);
            return true;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            spdlog::error("Failed to link program: {}", infoLog);
            return true;
        }
    }

    return false;
}

Shader AssetManager::loadShader(const std::string& vertexShader, const std::string& fragShader) const {
    spdlog::info("Loading vertex shader: {}", vertexShader);
    spdlog::info("Loading fragment shader: {}", fragShader);

    auto vertexCodeStr = readText(vertexShader);
    auto fragCodeStr = readText(fragShader);

    if (!vertexCodeStr.has_value() || !fragCodeStr.has_value()) {
        FATAL("Failed to read shader code");
    }

    const char* vertexCode = vertexCodeStr.value().c_str();
    const char* fragCode = fragCodeStr.value().c_str();
    
    // Compile vertex shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);

    if (checkCompilerErrors(vertex, "VERTEX_SHADER")) {
        FATAL("Vertex shader compilation failed");
    }

    // Compile fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, nullptr);
    glCompileShader(fragment);

    if (checkCompilerErrors(fragment, "FRAGMENT_SHADER")) {
        FATAL("Fragment shader compilation failed");
    }

    // Link shader program
    Shader shader;
    shader.setId(glCreateProgram());
    glAttachShader(shader.getId(), vertex);
    glAttachShader(shader.getId(), fragment);
    glLinkProgram(shader.getId());

    if (checkCompilerErrors(shader.getId(), "PROGRAM")) {
        FATAL("Shader program linking failed");
    }

    // Cleanup
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

Texture AssetManager::loadTextureFromImage(const Texture::TextureType& type, const std::string& path, bool gamma) {
    Texture texture;
    texture.path = path;
    texture.type = type;
    glGenTextures(1, &texture.id);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        spdlog::info("Texture: {} loaded.", path);
    } else {
        stbi_image_free(data);
        FATAL("Texture failed to load at path: {}", path);
    }

    return texture;
}

std::vector<Texture> AssetManager::loadMaterialTextures(
    const std::string& directory, 
    const Texture::TextureType& typeName, 
    aiMaterial *mat, 
    aiTextureType type
) {
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        // Check if texture was loaded before
        bool skip = false;
        for (const auto& loaded_texture : this->m_texturesLoaded) {
            if (std::strcmp(loaded_texture.path.data(), str.C_Str()) == 0) {
                textures.push_back(loaded_texture);
                skip = true;
                break;
            }
        }
        
        if (!skip) {   
            Texture texture = loadTextureFromImage(typeName, directory + str.C_Str());
            textures.push_back(texture);
            this->m_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

void AssetManager::processMesh(Entity& entity, const std::string& directory, const aiScene* scene, aiMesh* mesh) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Process vertices
    vertices.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        
        // Position
        vertex.Position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // Normals
        if (mesh->HasNormals()) {
            vertex.Normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            };
        }

        // Texture coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        } else {
            vertex.TexCoords = {0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process materials
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

        // Load textures for this material
        auto diffuseMaps = loadMaterialTextures(directory, Texture::TextureType::Diffuse, material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        auto specularMaps = loadMaterialTextures(directory, Texture::TextureType::Specular, material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        auto normalMaps = loadMaterialTextures(directory, Texture::TextureType::Normals, material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        auto heightMaps = loadMaterialTextures(directory, Texture::TextureType::Height, material, aiTextureType_AMBIENT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }
    
    // Set components
    entity.getComponentManager().set(Mesh(vertices, indices));
    entity.getComponentManager().set(MeshRenderer(
        loadShader("assets\\shaders\\default\\default.vert", "assets\\shaders\\default\\default.frag"), 
        textures
    ));
}

void AssetManager::processNode(Entity& entity, const std::string& directory, const aiScene* scene, aiNode* node) {
    auto& hierarchy = entity.getComponentManager().get<Hierarchy>().value().get();

    // Process all meshes in the node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        Entity child(mesh->mName.C_Str());
        spdlog::info("Created Entity with id: {}", mesh->mName.C_Str());

        processMesh(child, directory, scene, mesh);
        hierarchy.add(child);
    }

    // Process all child nodes recursively
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        Entity child(node->mChildren[i]->mName.C_Str());
        child.getComponentManager().set(Hierarchy());
        spdlog::info("Created Entity with id: {}", node->mChildren[i]->mName.C_Str());

        processNode(child, directory, scene, node->mChildren[i]);
        hierarchy.add(child);
    }
}

Entity AssetManager::loadEntity(const std::string& path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        FATAL("Failed to load model: {}", path);
    }
    
    Entity entity(scene->mRootNode->mName.C_Str());
    entity.getComponentManager().set(Hierarchy());
    spdlog::info("Created Entity with id: {}", scene->mRootNode->mName.C_Str());

    const std::string directory = path.substr(0, path.find_last_of('\\')) + '\\';
    processNode(entity, directory, scene, scene->mRootNode);

    return entity;
}

Texture AssetManager::loadCubemap(const std::vector<std::string>& faces) {
    Texture texture;
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.id);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format = nrComponents == 1 ? GL_RED : 
                            nrComponents == 3 ? GL_RGB : GL_RGBA;

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            spdlog::error("Cubemap texture failed to load at path: {}", faces[i]);
            stbi_image_free(data);
        }
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture;
}

}