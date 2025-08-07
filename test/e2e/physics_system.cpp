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
    std::vector<std::string> faces = {
        "assets\\textures\\skybox\\sky_36\\pz.png",
        "assets\\textures\\skybox\\sky_36\\nz.png",
        "assets\\textures\\skybox\\sky_36\\py.png",
        "assets\\textures\\skybox\\sky_36\\ny.png",
        "assets\\textures\\skybox\\sky_36\\nx.png",
        "assets\\textures\\skybox\\sky_36\\px.png"
    };

    ren::assets::AssetManager assetManager;
    auto ballShader = assetManager.loadShader("assets\\shaders\\planetary_system\\planetary.vert", "assets\\shaders\\planetary_system\\planetary.frag");
    auto skyboxShader = assetManager.loadShader("assets\\shaders\\skybox\\skybox.vert", "assets\\shaders\\skybox\\skybox.frag");
    unsigned int cubemapId = assetManager.loadCubemap(faces);
    unsigned int ballTextureId = assetManager.loadTextureFromImage("assets\\textures\\planetary_system\\Earth.jpg");

    ren::ecs::components::shaders::Texture ballTexture;
    ballTexture.id = ballTextureId;
    ballTexture.path = "assets\\textures\\Earth.jpg";
    ballTexture.type = "texture_diffuse";

    ren::ecs::components::shaders::Texture skyboxTexture;
    skyboxTexture.id = cubemapId;
    skyboxTexture.path = "assets\\textures\\skybox\\stars\\";
    skyboxTexture.type = "texture_cubemap";

    auto& entityManager = scene.getEntityManager();
    auto& systemManager = scene.getSystemManager();

    ren::ecs::entities::Entity ball("ball");
    ren::ecs::entities::Entity skybox("skybox");
    auto& ballComponentManager = ball.getComponentManager();
    auto& skyboxComponentManager = skybox.getComponentManager();

    ballComponentManager.set(ren::ecs::components::Transform());
    ballComponentManager.add<ren::physics::components::RigidBody>();
    ballComponentManager.add<ren::ecs::components::meshes::Sphere>();
    ballComponentManager.set(ren::ecs::components::MeshRenderer(ballShader, {ballTexture}));

    skyboxComponentManager.add<ren::ecs::components::meshes::Cube>();
    skyboxComponentManager.set(ren::ecs::components::MeshRenderer(skyboxShader, {skyboxTexture}));

    entityManager.add(ball);
    entityManager.add(skybox);

    ren::physics::systems::PhysicsSystem physicsSystem;
    systemManager.set(physicsSystem);
}