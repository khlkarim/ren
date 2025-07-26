#include <core/Window.hpp>
#include <io/AssetManager.hpp>

int main()
{
    ren::Window window("Backpack", 1980, 1080);
    ren::Scene scene;

    ren::io::AssetManager assetManager;
    ren::Entity entity(assetManager.loadEntity("assets\\models\\backpack\\backpack.obj"));

    entity.setComponent<ren::components::Transform>(ren::components::Transform());

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