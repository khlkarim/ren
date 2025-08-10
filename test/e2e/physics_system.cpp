#include "ren/core.hpp"
#include "ren/ecs.hpp"
#include "ren/physics.hpp"
#include "ren/renderer.hpp"
#include "ren/io.hpp"
#include "ren/assets.hpp"

// Forward declarations
void initializeScene(ren::core::Scene& scene);
void setupSkybox(ren::core::Scene& scene, ren::assets::AssetManager& assetManager);
void setupBalls(ren::core::Scene& scene, ren::assets::AssetManager& assetManager);

int main()
{
    constexpr int kWindowWidth = 1980;
    constexpr int kWindowHeight = 1080;
    
    // Initialize window and input devices
    ren::core::Window window("Physics", kWindowWidth, kWindowHeight);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);

    // Create and initialize scene
    ren::core::Scene scene;
    initializeScene(scene);

    // Set up rendering
    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem cameraSystem;
    renderer.setRenderTarget(window.getGlfwWindow());

    // Main game loop
    float lastFrameTime = static_cast<float>(glfwGetTime());
    while (window.isOpen())
    {   
        // Calculate delta time
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Update and render
        cameraSystem.update(deltaTime, renderer.getCamera());
        scene.update(deltaTime);
        renderer.render(scene);
    }

    return 0;
}

void initializeScene(ren::core::Scene& scene)
{
    // Initialize asset manager
    ren::assets::AssetManager assetManager;
    
    // Setup skybox and physical objects
    setupSkybox(scene, assetManager);
    setupBalls(scene, assetManager);
    
    // Add physics system to the scene
    auto& systemManager = scene.getSystemManager();
    systemManager.set(ren::physics::systems::PhysicsSystem());
}

void setupSkybox(ren::core::Scene& scene, ren::assets::AssetManager& assetManager)
{
    const std::vector<std::string> kSkyboxFaces = {
        "assets\\textures\\skybox\\sky_36\\pz.png",
        "assets\\textures\\skybox\\sky_36\\nz.png",
        "assets\\textures\\skybox\\sky_36\\py.png",
        "assets\\textures\\skybox\\sky_36\\ny.png",
        "assets\\textures\\skybox\\sky_36\\nx.png",
        "assets\\textures\\skybox\\sky_36\\px.png"
    };

    auto skyboxShader = assetManager.loadShader(
        "assets\\shaders\\skybox\\skybox.vert", 
        "assets\\shaders\\skybox\\skybox.frag"
    );
    
    unsigned int cubemapId = assetManager.loadCubemap(kSkyboxFaces);
    
    ren::ecs::components::shaders::Texture skyboxTexture;
    skyboxTexture.id = cubemapId;
    skyboxTexture.path = "assets\\textures\\skybox\\stars\\";
    skyboxTexture.type = "texture_cubemap";

    // Create skybox entity
    ren::ecs::entities::Entity skybox("skybox");
    auto& componentManager = skybox.getComponentManager();
    componentManager.add<ren::ecs::components::meshes::Cube>();
    componentManager.set(ren::ecs::components::MeshRenderer(skyboxShader, {skyboxTexture}));
    
    scene.getEntityManager().add(skybox);
}

void setupBalls(ren::core::Scene& scene, ren::assets::AssetManager& assetManager)
{
    // Load shaders and textures
    auto ballShader = assetManager.loadShader(
        "assets\\shaders\\planetary_system\\planetary.vert", 
        "assets\\shaders\\planetary_system\\planetary.frag"
    );
    
    unsigned int earthTextureId = assetManager.loadTextureFromImage("assets\\textures\\planetary_system\\Earth.jpg");
    unsigned int sunTextureId = assetManager.loadTextureFromImage("assets\\textures\\planetary_system\\Sun.jpg");
    
    ren::ecs::components::shaders::Texture earthTexture;
    earthTexture.id = earthTextureId;
    earthTexture.path = "assets\\textures\\Earth.jpg";
    earthTexture.type = "texture_diffuse";

    ren::ecs::components::shaders::Texture sunTexture;
    sunTexture.id = sunTextureId;
    sunTexture.path = "assets\\textures\\Sun.jpg";
    sunTexture.type = "texture_diffuse";

    auto& entityManager = scene.getEntityManager();

    // Create first static ball
    ren::ecs::entities::Entity staticBall1("ball1");
    auto& scm1 = staticBall1.getComponentManager();
    
    scm1.set(ren::ecs::components::Transform());
    scm1.add<ren::physics::components::RigidBody>();
    scm1.add<ren::ecs::components::meshes::Sphere>();
    scm1.set(ren::ecs::components::MeshRenderer(ballShader, {earthTexture}));
    scm1.add<ren::physics::components::colliders::SphereCollider>();
    scm1.get<ren::ecs::components::Transform>().value().get().setPosition(glm::vec3(-10.0f, -0.5f, 0.0f));
    scm1.get<ren::physics::components::RigidBody>().value().get().setMass(0.0f);
    
    entityManager.add(staticBall1);

    // Create second static ball
    ren::ecs::entities::Entity staticBall2("ball2");
    auto& scm2 = staticBall2.getComponentManager();
    
    scm2.set(ren::ecs::components::Transform());
    scm2.add<ren::physics::components::RigidBody>();
    scm2.add<ren::ecs::components::meshes::Sphere>();
    scm2.set(ren::ecs::components::MeshRenderer(ballShader, {earthTexture}));
    scm2.add<ren::physics::components::colliders::SphereCollider>();
    scm2.get<ren::ecs::components::Transform>().value().get().setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
    scm2.get<ren::physics::components::RigidBody>().value().get().setMass(0.0f);
    
    entityManager.add(staticBall2);

    // Create dynamic ball (sun)
    ren::ecs::entities::Entity dynamicBall("ball3");
    auto& dcm = dynamicBall.getComponentManager();
    
    dcm.set(ren::ecs::components::Transform());
    dcm.add<ren::physics::components::RigidBody>();
    dcm.add<ren::ecs::components::meshes::Sphere>();
    dcm.set(ren::ecs::components::MeshRenderer(ballShader, {sunTexture}));
    dcm.add<ren::physics::components::colliders::SphereCollider>();
    dcm.get<ren::ecs::components::Transform>().value().get().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    dcm.get<ren::physics::components::RigidBody>().value().get().setVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));
    dcm.get<ren::physics::components::RigidBody>().value().get().setMass(1.0f);
    
    entityManager.add(dynamicBall);
}