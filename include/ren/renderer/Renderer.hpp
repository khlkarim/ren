#pragma once

#include <glm/glm.hpp>
#include <ren/core/Scene.hpp>
#include <ren/core/Window.hpp>
#include <ren/renderer/Camera.hpp>

namespace ren::ecs::entities { class Entity; }
namespace ren::ecs::components { class Hierarchy; }

namespace ren::renderer
{

class Renderer
{
public:
    void render(const core::Scene& scene) const;
    void render(
        const ren::ecs::entities::Entity& entity,
        const glm::mat4& projection = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f),
        const glm::mat4& model = glm::mat4(1.0f)
    ) const;

    Camera& getCamera();
    const Camera& getCamera() const;
    void setCamera(const Camera& cam);

    GLFWwindow* getRenderTarget();
    const GLFWwindow* getRenderTarget() const;
    void setRenderTarget(GLFWwindow* target);

private:
    Camera camera;
    GLFWwindow* renderTarget;
};

}