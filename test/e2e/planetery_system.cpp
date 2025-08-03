#include <core/Scene.hpp>
#include <core/Window.hpp>
#include <io/devices/Mouse.hpp>
#include <io/devices/Keyboard.hpp>
#include <assets/AssetManager.hpp>
#include <components/meshes/Sphere.hpp>
#include <components/Mesh.hpp>
#include <components/Transform.hpp>
#include <components/MeshRenderer.hpp>
#include <systems/CameraSystem.hpp>
#include <systems/SystemManager.hpp>

//Scene
ren::Scene CreateSystem();
void updateSystem(ren::Scene& scene, const float dt);

//Planet
struct Planet
{
    std::string name;
    glm::vec3 initPos;
    glm::vec3 rotAxis;
    float absoluteRotSpeed;
    float relativeRotSpeed;
};
std::vector<Planet> getPlanets();
void updatePlanet(ren::Entity& instance, const Planet& planet, const float dt);

int main()
{
    ren::Window window("Planetary System", 1980, 1080);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);

    ren::Scene scene(CreateSystem());
    ren::systems::SystemManager systemManager;
    systemManager.add<ren::systems::CameraSystem>();

    double lastTime = glfwGetTime();
    while(window.isOpen()) 
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        updateSystem(scene, deltaTime);
        systemManager.update(deltaTime, scene);
        window.render(scene);
    }

    return 0;
}

ren::Scene CreateSystem()
{
    ren::Scene scene;    
    auto& hierarchy = scene.getHierarchy();

    ren::assets::AssetManager assetManager;
    auto shader = assetManager.loadShader(
        "assets\\shaders\\planetary_system\\planetary.vert", 
        "assets\\shaders\\planetary_system\\planetary.frag"
    );
    
    ren::Entity planet;
    planet.setComponent<ren::components::Transform>(ren::components::Transform());
    planet.setComponent<ren::components::Mesh>(ren::components::meshes::Sphere());

    std::vector<Planet> planets = getPlanets();
    
    auto& t = planet.getComponent<ren::components::Transform>().value().get();

    ren::components::shaders::Texture earthTexture;
    earthTexture.type = "texture_diffuse";

    for(const auto& p : planets)
    {
        earthTexture.path = "assets\\textures\\planetary_system\\" + p.name + ".jpg";
        earthTexture.id = assetManager.loadTextureFromImage(earthTexture.path);
        planet.setComponent<ren::components::MeshRenderer>(ren::components::MeshRenderer(shader, {earthTexture}));
        t.setPosition(p.initPos);
    
        planet.setId(p.name);
        hierarchy.add(planet);

    }

    return scene;
}

void updateSystem(ren::Scene& scene, const float dt)
{
    auto& hierarchy = scene.getHierarchy();
    std::vector<Planet> planets = getPlanets();
    
    for(const auto& planet : planets)
    {
        auto& instance = hierarchy.get(planet.name).value().get();
        updatePlanet(instance, planet, dt);
    }
}

std::vector<Planet> getPlanets()
{
    return {
        {
            "Sun",
            glm::vec3(0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            0.0f,
            10.0f
        },
        {
            "Earth",
            glm::vec3(2.0f),
            glm::normalize(glm::cross(glm::vec3(2.0f), glm::vec3(1.0f, 0.0f, 0.0f))),
            100.0f,
            100.0f
        },
        {
            "Jupiter",
            glm::vec3(4.0f, 4.0f, 0.0f),
            glm::normalize(glm::cross(glm::vec3(4.0f), glm::vec3(1.0f, 0.0f, 0.0f))),
            80.0f,
            80.0f
        },
        {
            "Uranas",
            glm::vec3(6.0f, 0.0f, 6.0f),
            glm::normalize(glm::cross(glm::vec3(6.0f), glm::vec3(1.0f, 0.0f, 0.0f))),
            40.0f,
            40.0f
        },
        {
            "Mars",
            glm::vec3(8.0f),
            glm::normalize(glm::cross(glm::vec3(8.0f), glm::vec3(1.0f, 0.0f, 0.0f))),
            20.0f,
            20.0f
        }
    };
}

void updatePlanet(ren::Entity& instance, const Planet& planet, const float dt)
{
    auto& t = instance.getComponent<ren::components::Transform>().value().get();
    auto position = t.getPosition();
    auto right = glm::normalize(glm::cross(position, glm::vec3(0.0f, 1.0f, 0.0f)));

    if(position != glm::vec3(0.0f))
    {
        t.rotate(planet.relativeRotSpeed * dt, glm::normalize(glm::cross(position, right)));
    }
    else
    {
        t.rotate(planet.relativeRotSpeed * dt, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(planet.absoluteRotSpeed) * dt, planet.rotAxis);
    position = glm::vec3(rotation * glm::vec4(position, 1.0f));
    t.setPosition(position);
}