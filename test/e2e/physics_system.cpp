#include "ren/core.hpp"
#include "ren/ecs.hpp"
#include "ren/physics.hpp"
#include "ren/renderer.hpp"
#include "ren/io.hpp"
#include "ren/assets.hpp"

void initializeScene(ren::core::Scene& scene);

int main()
{
    std::vector<glm::vec3> directions = {
        {1.0f, 0.0f, 0.0f},
        {-1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, -1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, -1.0f},
    };

    ren::core::Window window("Physics", 1980, 1080);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);

    ren::core::Scene scene;
    initializeScene(scene);

    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem cameraSystem;
    renderer.setRenderTarget(window.getGLFWwindow());

    auto& entityManager = scene.getEntityManager();
    auto& rigidBody = entityManager.getComponent<ren::physics::components::RigidBody>("ball").value().get();

    float lastFrame = static_cast<float>(glfwGetTime());
    while(window.isOpen())
    {   
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        static float timeAccumulator = 0.0f;
        timeAccumulator += deltaTime;
        if (timeAccumulator >= 1.0f) {
            int randomIndex = rand() % directions.size();
            rigidBody.setVelocity(directions[randomIndex]);
            rigidBody.setAngularVelocity(directions[randomIndex]);
            timeAccumulator = 0.0f;
        }

        cameraSystem.update(deltaTime, renderer.getCamera());
        scene.update(deltaTime);
        renderer.render(scene);
    }

    return 0;
}

void initializeScene(ren::core::Scene& scene)
{
    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader("assets\\shaders\\planetary_system\\planetary.vert", "assets\\shaders\\planetary_system\\planetary.frag");
    unsigned int textureId = assetManager.loadTextureFromImage("assets\\textures\\planetary_system\\Earth.jpg");

    ren::ecs::components::shaders::Texture texture;
    texture.id = textureId;
    texture.path = "assets\\textures\\Earth.jpg";
    texture.type = "texture_diffuse";

    auto& entityManager = scene.getEntityManager();
    auto& systemManager = scene.getSystemManager();

    ren::ecs::entities::Entity ball("ball");
    auto& componentManager = ball.getComponentManager();

    componentManager.set(ren::ecs::components::Transform());
    componentManager.add<ren::physics::components::RigidBody>();
    componentManager.add<ren::ecs::components::meshes::Sphere>();
    componentManager.set<ren::ecs::components::MeshRenderer>(ren::ecs::components::MeshRenderer(shader, {texture}));

    entityManager.add(ball);

    ren::physics::systems::PhysicsSystem physicsSystem;
    systemManager.set(physicsSystem);
}