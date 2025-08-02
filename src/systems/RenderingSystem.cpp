#include <systems/RenderSystem.hpp>
using ren::systems::RenderingSystem;

void RenderingSystem::render(const Camera& camera, const components::Hierarchy& hierarchy) const
{
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    std::vector<std::string> entities = hierarchy.getChildren();

    for(const auto& entityId : entities)
    {
        this->render(*hierarchy.get(entityId), projection, view);
    }
}

void RenderingSystem::render(
    const Entity& entity,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::mat4& model
) const {
    glm::mat4 currModel = model;

    if(entity.has<ren::components::Transform>())
    {
        auto& transform = entity.getComponent<ren::components::Transform>().value().get();
        currModel *= transform.getModelMatrix();
    }

    if(entity.has<ren::components::Mesh, ren::components::MeshRenderer>()) 
    {
        auto& mesh = entity.getComponent<ren::components::Mesh>().value().get();
        auto& meshRenderer = entity.getComponent<ren::components::MeshRenderer>().value().get();
    
        ren::components::shaders::Shader shader = meshRenderer.getShader();
    
        shader.use();
    
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", currModel);
    
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
    
        for(unsigned int i = 0; i<meshRenderer.textures.size(); i++) 
        {
            glActiveTexture(GL_TEXTURE0 + i);
    
            std::string number;
            std::string name = meshRenderer.textures[i].type;
    
            if(name == "texture_diffuse") 
            {
                number = std::to_string(diffuseNr++);
            }
            else 
            {
                number = std::to_string(specularNr++);
            }
    
            shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, meshRenderer.textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
    
        glBindVertexArray(mesh.getVAO());
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    if(entity.has<ren::components::Hierarchy>())
    {
        auto& hierarchy = entity.getComponent<ren::components::Hierarchy>().value().get();
        std::vector<std::string> entities = hierarchy.getChildren();

        for(const auto& entityId : entities)
        {
            this->render(hierarchy.get(entityId).value(), projection, view, currModel);
        }
    }
}