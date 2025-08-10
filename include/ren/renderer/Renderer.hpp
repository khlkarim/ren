#pragma once

#include <glm/glm.hpp>
#include "core/Window.hpp"
#include "renderer/Camera.hpp"

namespace ren::core { class Scene; }
namespace ren::ecs::entities { class Entity; }
namespace ren::ecs::components { 
    class Hierarchy; 
    class MeshRenderer;
}

namespace ren::renderer
{

class Renderer
{
public:
    void render(const core::Scene& scene) const;
    
    void renderEntity(
        const ecs::entities::Entity& entity,
        const glm::mat4& projection = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f),
        const glm::mat4& model = glm::mat4(1.0f)
    ) const;
    
    void renderSkybox(
        const ecs::entities::Entity& skybox,
        const glm::mat4& projection = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f)
    ) const;
    
    Camera& getCamera();
    const Camera& getCamera() const;
    void setCamera(const Camera& camera);
    
    GLFWwindow* getRenderTarget();
    const GLFWwindow* getRenderTarget() const;
    void setRenderTarget(GLFWwindow* target);

private:
    void renderMesh(
        const ecs::entities::Entity& entity,
        const glm::mat4& projection = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f),
        const glm::mat4& model = glm::mat4(1.0f)
    ) const;
    void bindTextures(const ecs::components::MeshRenderer& meshRenderer) const;


private:
    Camera m_camera;
    GLFWwindow* m_renderTarget = nullptr;
};

}