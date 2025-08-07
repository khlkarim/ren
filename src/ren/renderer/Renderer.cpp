#include <glad/glad.h>

#include "ecs/components/Mesh.hpp"
#include "ecs/components/Hierarchy.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/MeshRenderer.hpp"
#include "ecs/components/shaders/Shader.hpp"

#include "renderer/Camera.hpp"
#include "ecs/entities/Entity.hpp"

#include "renderer/Renderer.hpp"
using ren::renderer::Renderer;
using ren::renderer::Camera;
using ren::ecs::entities::Entity;

void Renderer::render(const core::Scene& scene) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = this->camera.getViewMatrix();
    glm::mat4 projection = this->camera.getProjectionMatrix();

    auto& hierarchy = scene.getEntityManager();
    if(hierarchy.get("skybox"))
    {
        this->renderSkybox(*hierarchy.get("skybox"), projection, view);
    }

    std::vector<std::string> entities = hierarchy.getEntityIds();
    for(const auto& entityId : entities)
    {
        this->render(*hierarchy.get(entityId), projection, view);
    }

    glfwPollEvents();
    glfwSwapBuffers(this->renderTarget);
}

void Renderer::render(
    const Entity& entity,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::mat4& model
) const {
    glm::mat4 currModel = model;

    if(entity.getComponentManager().has<ren::ecs::components::Transform>())
    {
        auto& transform = entity.getComponentManager().get<ren::ecs::components::Transform>().value().get();
        currModel *= transform.getModelMatrix();
    }

    if(entity.getId() != "skybox" && entity.getComponentManager().has<ren::ecs::components::Mesh, ren::ecs::components::MeshRenderer>()) 
    {
        auto& mesh = entity.getComponentManager().get<ren::ecs::components::Mesh>().value().get();
        auto& meshRenderer = entity.getComponentManager().get<ren::ecs::components::MeshRenderer>().value().get();

        const auto& shader = meshRenderer.getShader();
        shader.use();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", currModel);

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;

        for(unsigned int i = 0; i < meshRenderer.textures.size(); i++) 
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = meshRenderer.textures[i].type;

            if(name == "texture_diffuse") number = std::to_string(diffuseNr++);
            else if(name == "texture_specular") number = std::to_string(specularNr++);
            else if(name == "texture_normal") number = std::to_string(normalNr++);

            shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, meshRenderer.textures[i].id);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(mesh.getVAO());
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    if(entity.getComponentManager().has<ren::ecs::components::Hierarchy>())
    {
        auto& hierarchy = entity.getComponentManager().get<ren::ecs::components::Hierarchy>().value().get();
        std::vector<std::string> entities = hierarchy.getChildren();

        for(const auto& entityId : entities)
        {
            this->render(hierarchy.get(entityId).value(), projection, view, currModel);
        }
    }
}

void Renderer::renderSkybox(
    const Entity& skybox,
    const glm::mat4& projection,
    const glm::mat4& view
) const
{
    auto& mesh = skybox.getComponentManager().get<ren::ecs::components::Mesh>().value().get();
    auto& meshRenderer = skybox.getComponentManager().get<ren::ecs::components::MeshRenderer>().value().get();
    const auto& shader = meshRenderer.getShader();
    shader.use();

    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
    shader.setMat4("projection", projection);
    shader.setMat4("view", viewNoTranslation);

    glBindVertexArray(mesh.getVAO());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, meshRenderer.textures[0].id);

    glDepthMask(GL_FALSE);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);

    glBindVertexArray(0);
}

Camera& Renderer::getCamera() {
    return camera;
}

const Camera& Renderer::getCamera() const {
    return camera;
}

void Renderer::setCamera(const Camera& cam) {
    camera = cam;
}

GLFWwindow* Renderer::getRenderTarget() {
    return renderTarget;
}

const GLFWwindow* Renderer::getRenderTarget() const {
    return renderTarget;
}

void Renderer::setRenderTarget(GLFWwindow* target) {
    renderTarget = target;
}