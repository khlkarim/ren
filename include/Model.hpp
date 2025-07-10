#ifndef MODEL_HPP
#define MODEL_HPP

#include <spdlog/spdlog.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <stb_image.h>
#include "Transform.hpp"
#include "Mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    Model(const std::string& path);
    virtual ~Model();
    void render();
    friend bool operator==(const Model& m1, const Model& m2);
    
private:
    void load(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

public: 
    Transform transform;

private:
    boost::uuids::uuid _id;
    std::string _path;
    std::vector<Mesh> meshes;
};

#endif // MODEL_HPP