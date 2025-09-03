#include "ren/assets.hpp"
#include "ren/core.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"

std::vector<unsigned char> getInitialState();
std::vector<ren::ecs::components::shaders::Texture> createTextures();
std::vector<GLuint> createFramebuffers(const std::vector<ren::ecs::components::shaders::Texture>& textures);

int main()
{
    ren::core::Window window("Cellular Automata", 1024, 1024);
    ren::core::Scene scene;
    
    ren::renderer::Renderer renderer;
    renderer.setRenderTarget(window.getGlfwWindow());
    renderer.getCamera().setAspectRatio(1);

    ren::assets::AssetManager assetManager;

    auto& displayShader = assetManager.loadShader(
        "assets\\shaders\\textured\\textured.vert",
        "assets\\shaders\\textured\\textured.frag"
    );
    auto& simShader = assetManager.loadShader(
        "assets\\shaders\\cellular_automata\\cellular_automata.vert",
        "assets\\shaders\\cellular_automata\\cellular_automata.frag"
    );

    auto textures = createTextures();
    auto fbos = createFramebuffers(textures);

    ren::ecs::entities::Entity plane("plane");
    plane.getComponentManager().set(ren::ecs::components::meshes::Quad(5, 5));
    plane.getComponentManager().set(ren::ecs::components::MeshRenderer(simShader));

    scene.getEntityManager().add(plane);
    auto& universe = scene.getEntityManager().get("plane").value().get();
    auto& mr = universe.getComponentManager().get<ren::ecs::components::MeshRenderer>().value().get();

    int readTexture = 0;
    int writeTexture = 1;

    while (window.isOpen()) {
        // Step 1: Simulate next state into writeTexture
        mr.setShader(simShader);
        mr.setTextures({textures[readTexture]});
        glBindFramebuffer(GL_FRAMEBUFFER, fbos[writeTexture]);
        renderer.render(scene);

        // Step 2: Display writeTexture to screen
        mr.setShader(displayShader);
        mr.setTextures({textures[writeTexture]});
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        renderer.render(scene);

        // Step 3: Swap textures for next frame
        std::swap(readTexture, writeTexture);
    }

    return 0;
}

std::vector<unsigned char> getInitialState()
{
    int width = 128;
    int height = 128;

    // 1 byte per cell (GL_R8)
    std::vector<unsigned char> initialData(width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Random 0 or 1
            static bool seeded = false;
            if (!seeded) {
                srand(static_cast<unsigned int>(time(nullptr)));
                seeded = true;
            }
            initialData[y * width + x] = (rand() % 2) ? 255 : 0;
        }
    }

    return initialData;
}

std::vector<ren::ecs::components::shaders::Texture> createTextures()
{
    std::vector<ren::ecs::components::shaders::Texture> textures(2);
    
    for (int i = 0; i < 2; ++i) {
        glGenTextures(1, &textures[i].id);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 128, 128, 0, GL_RED, GL_UNSIGNED_BYTE, getInitialState().data());
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // for neighbor sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    return textures;
}

std::vector<GLuint> createFramebuffers(const std::vector<ren::ecs::components::shaders::Texture>& textures)
{
    std::vector<GLuint> fbos(2);
    
    for (int i = 0; i < 2; ++i) {
        glGenFramebuffers(1, &fbos[i]);
        glBindFramebuffer(GL_FRAMEBUFFER, fbos[i]);
    
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[i].id, 0);
    
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            spdlog::error("FBO {} incomplete!", i);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return fbos;
}