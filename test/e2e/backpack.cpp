#include <core/Window.hpp>
#include <io/AssetManager.hpp>

void setShader(ren::Entity& entity, ren::components::shaders::Shader& shader);

int main()
{
    ren::Window window("Backpack", 1980, 1080);
    ren::Scene scene;

    ren::io::AssetManager assetManager;
    ren::Entity entity(assetManager.loadEntity("assets\\models\\backpack\\backpack.obj"));

    entity.setComponent<ren::components::Transform>(ren::components::Transform());
    setShader(entity, assetManager.loadShader("assets\\shaders\\backpack\\backpack.vert", "assets\\shaders\\backpack\\backpack.frag"));

    auto& sceneHierarchy = scene.getHierarchy();
    sceneHierarchy.add(entity);

    float lastFrame = static_cast<float>(glfwGetTime());
    while(window.isOpen()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        auto& t = sceneHierarchy.getComponent<ren::components::Transform>(entity.getId());
        t.rotate(30 * delta, glm::vec3(0.0f, 1.0f, 0.0f));

        window.render(scene);
    }

    return 0;    
}

void setShader(ren::Entity& entity, ren::components::shaders::Shader& shader)
{
    if(entity.has<ren::components::MeshRenderer>())
    {
        auto& mr = entity.getComponent<ren::components::MeshRenderer>();
        mr.setShader(shader);
    }

    if(entity.has<ren::components::Hierarchy>())
    {
        auto& h = entity.getComponent<ren::components::Hierarchy>();
        std::vector<std::string> children = h.getChildren();

        for(const auto& childId : children)
        {
            setShader(h.get(childId), shader);
        }
    }
}