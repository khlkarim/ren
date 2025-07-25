#include <core/Window.hpp>
#include <io/AssetManager.hpp>

int main()
{
    ren::Window window("Backpack", 1980, 1080);
    ren::Scene scene;

    ren::io::AssetManager assetManager;
    ren::Entity entity(assetManager.loadEntity("assets\\models\\backpack\\backpack.obj"));

    auto& sceneHierarchy = scene.getHierarchy();
    sceneHierarchy.add(entity);

    while(window.isOpen())
    {
        window.render(scene);
    }

    return 0;    
}