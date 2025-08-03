#include <core/Scene.hpp>
#include <core/Window.hpp>
#include <assets/AssetManager.hpp>
#include <components/meshes/Sphere.hpp>

int main()
{
    ren::Window window("Sphere", 1980, 1080);
    ren::Scene scene;

    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets\\shaders\\default\\default.vert", 
        "assets\\shaders\\default\\default.frag"
    );

    ren::Entity ball("ball");
    ball.setComponent<ren::components::Mesh>(ren::components::meshes::Sphere());
    ball.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {}));

    auto& h = scene.getHierarchy();
    h.add(ball);

    while(window.isOpen())
    {
        window.render(scene);
    }

    return 0;
}