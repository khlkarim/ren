#include "Model.hpp"

Model::Model(const std::string& path)
    : shader(
        "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\shaders\\default.vert",
        "C:\\Users\\karim\\dev\\workspaces\\personal\\ren\\assets\\shaders\\default.frag"
    )
{
    spdlog::info("Loading Model");
    this->_id = boost::uuids::random_generator()();
    this->load(path);
    spdlog::info("Finished loading model");
}

Model::~Model()
{
    spdlog::info("Unloaded model with ID: {}", boost::uuids::to_string(this->_id));
}

void Model::render(const glm::mat4& projection, const glm::mat4& view)
{
    this->shader.use();

    this->shader.setMat4("projection", projection);
    this->shader.setMat4("view", view);
    this->shader.setMat4("model", this->transform.getModelMatrix());

    for(unsigned int i = 0; i<this->meshes.size(); i++)
    {
        this->meshes[i].render(this->shader);
    }
}

bool operator==(const Model& m1, const Model& m2) 
{
    return m1._id == m2._id;
}

void Model::load(const std::string& path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        spdlog::error("Failed to load model: {}", import.GetErrorString());
        return;
    }
    this->_path = path.substr(0, path.find_last_of('\\'));
    spdlog::info("Loaded the scene object");

    processNode(scene->mRootNode, scene);
} 

void Model::processNode(aiNode *node, const aiScene *scene)
{
    spdlog::info("Processing node: {}", node->mName.C_Str());
    for(unsigned int i = 0; i<node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh, scene)); 
    }

    for(unsigned int i = 0; i<node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
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

        std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
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
            texture.id = TextureFromFile(str.C_Str(), this->_path);
            texture.type = typeName;
            texture.path = str.C_Str();

            this->textures_loaded.push_back(texture);
            textures.push_back(texture);
        }
    }

    return textures;
}


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
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