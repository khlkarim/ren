#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/io.hpp"
#include "ren/renderer.hpp"

namespace {

void setupCubes(ren::core::Scene& scene, const ren::ecs::components::shaders::Shader& shader) {
    auto& entityManager = scene.getEntityManager();
    
    // Create first cube
    ren::ecs::entities::Entity cube1;
    auto& componentManager1 = cube1.getComponentManager();
    componentManager1.add<ren::ecs::components::Transform>();
    componentManager1.add<ren::ecs::components::meshes::Cube>();
    componentManager1.set(ren::ecs::components::MeshRenderer(shader, {}));
    cube1.setId("cube-1");
    entityManager.add(cube1);
    
    // Create second cube
    ren::ecs::entities::Entity cube2;
    auto& componentManager2 = cube2.getComponentManager();
    componentManager2.add<ren::ecs::components::Transform>();
    componentManager2.add<ren::ecs::components::meshes::Cube>();
    componentManager2.set(ren::ecs::components::MeshRenderer(shader, {}));
    componentManager2.get<ren::ecs::components::Transform>().value().get().setPosition(
        glm::vec3(0.0f, 0.0f, 12.0f));
    cube2.setId("cube-2");
    entityManager.add(cube2);
}

glm::vec3 calculateLightColor(double currentTime) {
    return glm::vec3(
        glm::cos(currentTime) * glm::cos(currentTime),
        glm::sin(currentTime) * glm::sin(currentTime),
        glm::cos(currentTime - glm::pi<double>() / 4) * 
        glm::cos(currentTime - glm::pi<double>() / 4)
    );
}

void updateShaders(ren::core::Scene& scene, double currentTime) {
    auto& entityManager = scene.getEntityManager();
    
    const auto lightPos = glm::vec3(0.0f, 0.0f, 6.0f);
    const auto lightColor = calculateLightColor(currentTime);
    
    for (const auto& cubeId : {"cube-1", "cube-2"}) {
        auto& meshRenderer = entityManager.getComponent<ren::ecs::components::MeshRenderer>(cubeId)
                                        .value().get();
        auto& shader = meshRenderer.getShader();
        shader.setVec3("ulightPos", lightPos);
        shader.setVec3("ulightColor", lightColor);
    }
}

} // anonymous namespace

int main() {
    // Initialize window and input devices
    constexpr int kWindowWidth = 1980;
    constexpr int kWindowHeight = 1080;
    ren::core::Window window("Input System Test", kWindowWidth, kWindowHeight);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);
    
    // Load assets
    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets\\shaders\\lighting\\lighting.vert", 
        "assets\\shaders\\lighting\\lighting.frag"
    );

    // Setup scene
    ren::core::Scene scene;
    setupCubes(scene, shader);
    
    // Initialize renderer
    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem cameraSystem;
    renderer.setRenderTarget(window.getGlfwWindow());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.getGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Main loop
    double lastTime = glfwGetTime();
    while (window.isOpen()) {
        const double currentTime = glfwGetTime();
        const float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        updateShaders(scene, currentTime);
        cameraSystem.update(deltaTime, renderer.getCamera());
        renderer.render(scene);

        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example window
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is a demo window!");
        static float f = 0.0f;
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        if (ImGui::Button("Close")) 
            glfwSetWindowShouldClose(window.getGlfwWindow(), true);
        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window.getGlfwWindow());
    glfwTerminate();

    return 0;
}