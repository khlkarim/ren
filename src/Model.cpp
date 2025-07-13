#include "Model.hpp"

Model::Model()
{
    spdlog::info("Model created");
}

Model::~Model()
{
    spdlog::info("Model destroyed");
}

bool Model::addMesh(const std::shared_ptr<Mesh>& mesh)
{
    if(!mesh) return false;

    if (std::find(this->meshes.begin(), this->meshes.end(), mesh) == this->meshes.end())
    {
        this->meshes.push_back(mesh);
        return true;
    } 

    return false;
}

bool Model::removeMesh(const std::shared_ptr<Mesh>& mesh)
{
    if(!mesh) return false;

    auto it = std::find(this->meshes.begin(), this->meshes.end(), mesh);
    if (it != this->meshes.end())
    {
        this->meshes.erase(it);
        return true;
    }
   
    return false;
}

void Model::render(const glm::mat4& projection, const glm::mat4& view)
{
    for(unsigned int i = 0; i<this->meshes.size(); i++)
    {
        this->meshes[i]->render(projection, view, this->transform.getModelMatrix());
    }
}