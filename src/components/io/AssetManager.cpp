#include "AssetManager.hpp"

std::optional<Shader> AssetManager::loadShader(const std::string& vertexShader, const std::string& fragShader)
{
    spdlog::info("Loading vertex shader: {}", vertexShader);
    spdlog::info("Loading fragment shader: {}", fragShader);

    std::optional<std::string> vertexCodeStr = this->readText(vertexShader);
    std::optional<std::string> fragCodeStr = this->readText(fragShader);

    if(!vertexCodeStr.has_value() || !fragCodeStr.has_value()) return std::nullopt;

    const char* vertexCode = vertexCodeStr.value().c_str();
    const char* fragCode = fragCodeStr.value().c_str();
    
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    if(this->checkCompilerErrors(vertex, "VERTEX_SHADER"))
    {
        return std::nullopt;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, NULL);
    glCompileShader(fragment);

    if(this->checkCompilerErrors(fragment, "FRAGMENT_SHADER"))
    {
        return std::nullopt;
    }

    Shader shader;
    shader.setId(glCreateProgram());
    glAttachShader(shader.getId(), vertex);
    glAttachShader(shader.getId(), fragment);
    glLinkProgram(shader.getId());

    if(this->checkCompilerErrors(shader.getId(), "PROGRAM"))
    {
        return std::nullopt;
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

std::optional<Model> AssetManager::loadModel(const std::string& path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        spdlog::error("Failed to load model: {}", import.GetErrorString());
        return std::nullopt;
    }
    spdlog::info("Loaded the scene object");
    
    Model model;
    std::string directory = path.substr(0, path.find_last_of('\\'));
    processNode(scene->mRootNode, scene, model, directory);

    return model;
} 

void AssetManager::processNode(aiNode *node, const aiScene *scene, Model& model, const std::string& directory)
{
    spdlog::info("Processing node: {}", node->mName.C_Str());
    for(unsigned int i = 0; i<node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model.addMesh(std::make_shared<Mesh>(processMesh(mesh, scene, directory))); 
    }

    for(unsigned int i = 0; i<node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, model, directory);
    }
}

Mesh AssetManager::processMesh(aiMesh *mesh, const aiScene *scene, const std::string& directory)
{
    spdlog::info("Processing Mesh: {}", mesh->mName.C_Str());

    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i<mesh->mNumVertices; i++) 
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 texCoord;
            texCoord.x = mesh->mTextureCoords[0][i].x;
            texCoord.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = texCoord;
        } 
        else 
        {
            vertex.TexCoords = glm::vec2(0.0f);
        }

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i<mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j<face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex >= 0)
    {
        spdlog::info("Mesh has material. Loading...");
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    Mesh parsedMesh(vertices, indices, textures);

    std::optional<Shader> shader = this->loadShader("assets\\shaders\\backpack\\backpack.vert", "assets\\shaders\\backpack\\backpack.frag");

    if(shader.has_value()) 
    {
        parsedMesh.setShader(std::make_shared<Shader>(shader.value()));
    }

    return parsedMesh;
}

std::vector<Texture> AssetManager::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName, const std::string& directory)
{
    spdlog::info("Loading material textures");
    std::vector<Texture> textures;

    // Ensure we never push to textures_loaded while iterating it
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);

        auto it = std::find_if(
            this->textures_loaded.begin(), this->textures_loaded.end(),
            [&](const Texture& t) { return std::strcmp(t.path.data(), str.C_Str()) == 0; }
        );

        if (it != this->textures_loaded.end()) {
            textures.push_back(*it);
        } else {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();

            this->textures_loaded.push_back(texture);
            textures.push_back(texture);
        }
    }

    return textures;
}


unsigned int AssetManager::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename(path);
    if (directory.back() == '/' || directory.back() == '\\')
        filename = directory + filename;
    else
        filename = directory + "\\" + filename;
    spdlog::info("Texture from file: {}", filename);

    unsigned int textureID;
    glGenTextures(1, &textureID);
    spdlog::info("Generated the texture");

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    spdlog::info("Texture data pointer: {}", static_cast<void*>(data));
    if (data)
    {
        spdlog::info("Loaded Texture data");

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
        spdlog::info("Freed Texture data");
    }
    else
    {
        spdlog::error("Failed to load texture: {}", path);
        stbi_image_free(data);
    }

    return textureID;
}