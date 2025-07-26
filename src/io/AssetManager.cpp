#include "AssetManager.hpp"
using ren::Entity;
using ren::io::AssetManager;
using ren::components::Mesh;
using ren::components::MeshRenderer;
using ren::components::Transform;
using ren::components::Hierarchy;
using ren::components::meshes::Vertex;
using namespace ren::components::shaders;

Shader AssetManager::loadShader(const std::string& vertexShader, const std::string& fragShader)
{
    spdlog::info("Loading vertex shader: {}", vertexShader);
    spdlog::info("Loading fragment shader: {}", fragShader);

    std::optional<std::string> vertexCodeStr = this->readText(vertexShader);
    std::optional<std::string> fragCodeStr = this->readText(fragShader);

    if (!vertexCodeStr.has_value() || !fragCodeStr.has_value()) {
        fatal("Failed to read shader code");
    }

    const char* vertexCode = vertexCodeStr.value().c_str();
    const char* fragCode = fragCodeStr.value().c_str();
    
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    if (this->checkCompilerErrors(vertex, "VERTEX_SHADER")) {
        fatal("Vertex shader compilation failed");
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, NULL);
    glCompileShader(fragment);

    if (this->checkCompilerErrors(fragment, "FRAGMENT_SHADER")) {
        fatal("Fragment shader compilation failed");
    }

    Shader shader;
    shader.setId(glCreateProgram());
    glAttachShader(shader.getId(), vertex);
    glAttachShader(shader.getId(), fragment);
    glLinkProgram(shader.getId());

    if (this->checkCompilerErrors(shader.getId(), "PROGRAM")) {
        fatal("Shader program linking failed");
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

std::optional<std::string> AssetManager::readText(const std::string& path)
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
        return std::nullopt;
    }
    
    return result;
}

bool AssetManager::checkCompilerErrors(GLuint shader, const std::string& type) const
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
            return true;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error("Failed to link program: {}", infoLog);
            return true;
        }
    }

    return false;
}

ren::Entity AssetManager::loadEntity(const std::string& path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        fatal("Failed to load model: " + path);
    }
    
    Entity entity(scene->mRootNode->mName.C_Str());
    entity.setComponent<Hierarchy>(Hierarchy());
    spdlog::info("Created Entity with id: {}", scene->mRootNode->mName.C_Str());

    const std::string directory = path.substr(0, path.find_last_of('\\')) + '\\';
    this->processNode(entity, directory, scene, scene->mRootNode);

    return entity;
}

void AssetManager::processNode(Entity& entity, const std::string& directory, const aiScene* scene, aiNode* node)
{
    Hierarchy& hierarchy = entity.getComponent<Hierarchy>();

    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        Entity child(mesh->mName.C_Str());
        spdlog::info("Created Entity with id: {}", mesh->mName.C_Str());

        processMesh(child, directory, scene, mesh);			

        hierarchy.add(child);
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        Entity child(node->mChildren[i]->mName.C_Str());
        child.setComponent<Hierarchy>(Hierarchy());
        spdlog::info("Created Entity with id: {}", node->mChildren[i]->mName.C_Str());

        processNode(child, directory, scene, node->mChildren[i]);

        hierarchy.add(child);
    }
}  

void AssetManager::processMesh(Entity& entity, const std::string& directory, const aiScene* scene, aiMesh* mesh)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

    std::vector<Texture> diffuseMaps = loadMaterialTextures(directory, "texture_diffuse", material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(directory, "texture_specular",material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // std::vector<Texture> normalMaps = loadMaterialTextures(directory, "texture_normal", material, aiTextureType_HEIGHT);
    // textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // std::vector<Texture> heightMaps = loadMaterialTextures(directory, "texture_height", material, aiTextureType_AMBIENT);
    // textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    entity.setComponent<Mesh>(Mesh(vertices, indices));
    entity.setComponent<MeshRenderer>(MeshRenderer(
        this->loadShader("assets\\shaders\\backpack\\backpack.vert", "assets\\shaders\\backpack\\backpack.frag"), 
        textures
    ));
}

std::vector<Texture> AssetManager::loadMaterialTextures(
    const std::string& directory, 
    const std::string& typeName, 
    aiMaterial *mat, 
    aiTextureType type
) {
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {   
            Texture texture;
            texture.id = loadTextureFromImage(directory + str.C_Str());
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int AssetManager::loadTextureFromImage(const std::string& path, bool gamma)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        stbi_image_free(data);
        fatal("Texture failed to load at path: " + path);
    }

    return textureID;
}