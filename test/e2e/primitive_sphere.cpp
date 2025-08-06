#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"

int main()
{
    ren::core::Window window("Sphere", 1980, 1080);
    ren::core::Scene scene;

    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets\\shaders\\default\\default.vert", 
        "assets\\shaders\\default\\default.frag"
    );

    ren::ecs::entities::Entity ball("ball");
    ball.getComponentManager().set<ren::ecs::components::Mesh>(ren::ecs::components::meshes::Sphere());
    ball.getComponentManager().set<ren::ecs::components::MeshRenderer>(ren::ecs::components::MeshRenderer(shader, {}));

    auto& h = scene.getEntityManager();
    h.add(ball);

    ren::renderer::Renderer renderer;
    renderer.setRenderTarget(window.getGLFWwindow());

    while(window.isOpen())
    {
        renderer.render(scene);
    }

    return 0;
}