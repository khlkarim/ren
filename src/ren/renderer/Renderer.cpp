#include <string>
#include <vector>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Scene.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Camera.hpp"
#include "ecs/entities/Entity.hpp"
#include "ecs/components/Mesh.hpp"
#include "ecs/components/Hierarchy.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/MeshRenderer.hpp"
#include "ecs/components/shaders/Shader.hpp"

using ren::renderer::Renderer;
using ren::renderer::Camera;
using ren::ecs::entities::Entity;

void Renderer::render(const core::Scene& scene) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const glm::mat4 view = m_camera.getViewMatrix();
    const glm::mat4 projection = m_camera.getProjectionMatrix();

    auto& entityManager = scene.getEntityManager();
    
    // Render skybox first if it exists
    if (auto skyboxEntity = entityManager.get("skybox")) {
        renderSkybox(*skyboxEntity, projection, view);
    }

    // Render all other entities
    for (const auto& entityId : entityManager.getEntityIds()) {
        if (auto entity = entityManager.get(entityId)) {
            renderEntity(*entity, projection, view);
        }
    }

    glfwPollEvents();
    glfwSwapBuffers(m_renderTarget);
}

void Renderer::renderEntity(
    const Entity& entity,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::mat4& model
) const {
    glm::mat4 currentModel = model;

    // Apply entity's transform if it has one
    const auto& componentManager = entity.getComponentManager();
    if (componentManager.has<ren::ecs::components::Transform>()) {
        auto& transform = componentManager.get<ren::ecs::components::Transform>().value().get();
        currentModel *= transform.getModelMatrix();
    }

    // Render the entity if it has mesh and renderer components and is not the skybox
    if (entity.getId() != "skybox" && 
        componentManager.has<ren::ecs::components::Mesh>() && 
        componentManager.has<ren::ecs::components::MeshRenderer>()) 
    {
        renderMesh(entity, projection, view, currentModel);
    }

    // Recursively render children
    if (componentManager.has<ren::ecs::components::Hierarchy>()) {
        auto& hierarchy = componentManager.get<ren::ecs::components::Hierarchy>().value().get();
        
        for (const auto& childId : hierarchy.getChildren()) {
            if (auto childEntity = hierarchy.get(childId)) {
                renderEntity(childEntity.value().get(), projection, view, currentModel);
            }
        }
    }
}

void Renderer::renderMesh(
    const Entity& entity,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::mat4& model
) const {
    const auto& componentManager = entity.getComponentManager();
    auto& mesh = componentManager.get<ren::ecs::components::Mesh>().value().get();
    auto& meshRenderer = componentManager.get<ren::ecs::components::MeshRenderer>().value().get();
    
    const auto& shader = meshRenderer.getShader();
    shader.use();

    // Set shader uniforms
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);

    // Bind textures
    bindTextures(meshRenderer);

    // Draw mesh
    glBindVertexArray(mesh.getVao());
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::bindTextures(const ren::ecs::components::MeshRenderer& meshRenderer) const {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    const auto& shader = meshRenderer.getShader();
    const auto& textures = meshRenderer.getTextures();

    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        const std::string& name = textures[i].type;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
        }

        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::renderSkybox(
    const Entity& skybox,
    const glm::mat4& projection,
    const glm::mat4& view
) const {
    auto& mesh = skybox.getComponentManager().get<ren::ecs::components::Mesh>().value().get();
    auto& meshRenderer = skybox.getComponentManager().get<ren::ecs::components::MeshRenderer>().value().get();
    const auto& shader = meshRenderer.getShader();
    
    shader.use();

    // Remove translation from view matrix for skybox
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
    shader.setMat4("projection", projection);
    shader.setMat4("view", viewNoTranslation);

    glBindVertexArray(mesh.getVao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, meshRenderer.getTextures()[0].id);

    // Disable depth writing for skybox rendering
    glDepthMask(GL_FALSE);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);

    glBindVertexArray(0);
}

Camera& Renderer::getCamera() {
    return m_camera;
}

const Camera& Renderer::getCamera() const {
    return m_camera;
}

void Renderer::setCamera(const Camera& camera) {
    m_camera = camera;
}

GLFWwindow* Renderer::getRenderTarget() {
    return m_renderTarget;
}

const GLFWwindow* Renderer::getRenderTarget() const {
    return m_renderTarget;
}

void Renderer::setRenderTarget(GLFWwindow* target) {
    m_renderTarget = target;
}