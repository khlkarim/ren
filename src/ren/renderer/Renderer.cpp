#include <glad/glad.h>

#include <ren/ecs/components/Mesh.hpp>
#include <ren/ecs/components/Hierarchy.hpp>
#include <ren/ecs/components/Transform.hpp>
#include <ren/ecs/components/MeshRenderer.hpp>
#include <ren/ecs/components/shaders/Shader.hpp>

#include <ren/renderer/Camera.hpp>
#include <ren/ecs/entities/Entity.hpp>

#include <ren/renderer/Renderer.hpp>
using ren::renderer::Renderer;
using ren::renderer::Camera;
using ren::ecs::entities::Entity;

void Renderer::render(const core::Scene& scene) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = this->camera.getViewMatrix();
    glm::mat4 projection = this->camera.getProjectionMatrix();
    
    auto& hierarchy = scene.getHierarchy();
    std::vector<std::string> entities = hierarchy.getChildren();
    
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

    if(entity.has<ren::ecs::components::Transform>())
    {
        auto& transform = entity.getComponent<ren::ecs::components::Transform>().value().get();
        currModel *= transform.getModelMatrix();
    }

    if(entity.has<ren::ecs::components::Mesh, ren::ecs::components::MeshRenderer>()) 
    {
        auto& mesh = entity.getComponent<ren::ecs::components::Mesh>().value().get();
        auto& meshRenderer = entity.getComponent<ren::ecs::components::MeshRenderer>().value().get();
    
        const auto& shader = meshRenderer.getShader();
    
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

    if(entity.has<ren::ecs::components::Hierarchy>())
    {
        auto& hierarchy = entity.getComponent<ren::ecs::components::Hierarchy>().value().get();
        std::vector<std::string> entities = hierarchy.getChildren();

        for(const auto& entityId : entities)
        {
            this->render(hierarchy.get(entityId).value(), projection, view, currModel);
        }
    }
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