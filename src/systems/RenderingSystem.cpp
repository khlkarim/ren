#include <systems/RenderSystem.hpp>
using ren::systems::RenderingSystem;

void RenderingSystem::render(const Camera& camera, const Entity& entity) const
{
    auto& mesh = entity.getComponent<ren::components::Mesh>();
    auto& meshRenderer = entity.getComponent<ren::components::MeshRenderer>();
    auto& transform = entity.getComponent<ren::components::Transform>();

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = transform.getModelMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    ren::components::shaders::Shader shader = meshRenderer.getShader();

    shader.use();

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);

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

void RenderingSystem::render(Scene& scene) 
{
    const Camera& camera = scene.getCamera();
    ren::components::Hierarchy& hierarchy = scene.getHierarchy();

    glm::mat4 model(1.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    std::vector<std::string> entities = hierarchy.getEntitiesWith
        <ren::components::Mesh, 
        ren::components::MeshRenderer, 
        ren::components::Transform>();

    for(const auto& entityId : entities)
    {
        this->render(projection, view, model, hierarchy.get(entityId));
    }
}

void RenderingSystem::render(
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::mat4& model,
    Entity& entity
) {
    auto& mesh = entity.getComponent<ren::components::Mesh>();
    auto& meshRenderer = entity.getComponent<ren::components::MeshRenderer>();
    auto& transform = entity.getComponent<ren::components::Transform>();

    ren::components::shaders::Shader shader = meshRenderer.getShader();

    shader.use();

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model * transform.getModelMatrix());

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


    if(entity.has<ren::components::Hierarchy>())
    {
        auto& hierarchy = entity.getComponent<ren::components::Hierarchy>();

        std::vector<std::string> entities = hierarchy.getEntitiesWith
            <ren::components::Mesh, 
            ren::components::MeshRenderer, 
            ren::components::Transform>();

        for(const auto& entityId : entities)
        {
            this->render(projection, view, model * transform.getModelMatrix(), hierarchy.get(entityId));
        }
    }
}