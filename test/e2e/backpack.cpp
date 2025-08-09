#include "ren/core.hpp"
#include "ren/ecs.hpp"
#include "ren/assets.hpp"
#include "ren/renderer.hpp"

void setShader(ren::ecs::entities::Entity& entity, ren::ecs::components::shaders::Shader& shader);

int main()
{
    ren::core::Window window("Backpack", 1980, 1080);
    ren::core::Scene scene;

    ren::assets::AssetManager assetManager;
    auto entity = assetManager.loadEntity("assets\\models\\backpack\\backpack.obj");

    auto& componentManager = entity.getComponentManager();
    componentManager.add<ren::ecs::components::Transform>();
    
    setShader(entity, assetManager.loadShader(
        "assets\\shaders\\backpack\\backpack.vert", 
        "assets\\shaders\\backpack\\backpack.frag"
    ));

    auto& entityManager = scene.getEntityManager();
    entityManager.add(entity);

    ren::renderer::Renderer  renderer;
    renderer.setRenderTarget(window.getGLFWwindow());

    float lastFrame = static_cast<float>(glfwGetTime());
    while(window.isOpen()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& t = entityManager.getComponent<ren::ecs::components::Transform>(entity.getId()).value().get();
        t.rotate(30 * delta, glm::vec3(0.0f, 1.0f, 0.0f));

        renderer.render(scene);
    }

    return 0;    
}

void setShader(ren::ecs::entities::Entity& entity, ren::ecs::components::shaders::Shader& shader)
{
    auto& componentManager = entity.getComponentManager();

    if(componentManager.has<ren::ecs::components::MeshRenderer>())
    {
        auto& mr = componentManager.get<ren::ecs::components::MeshRenderer>().value().get();
        mr.setShader(shader);
    }

    if(componentManager.has<ren::ecs::components::Hierarchy>())
    {
        auto& h = componentManager.get<ren::ecs::components::Hierarchy>().value().get();
        std::vector<std::string> children = h.getChildren();

        for(const auto& childId : children)
        {
            setShader(h.get(childId).value(), shader);
        }
    }
}