#include "ren/core.hpp"
#include "ren/assets.hpp"
#include "ren/ecs.hpp"
#include "ren/renderer.hpp"
#include "ren/io.hpp"

// Forward declarations
namespace planetary_system {

// Planet data structure
struct Planet {
    std::string name;
    glm::vec3 initial_position;
    glm::vec3 rotation_axis;
    float absolute_rotation_speed;
    float relative_rotation_speed;
};

// Function declarations
std::vector<Planet> get_planets();
ren::core::Scene create_system();
void update_system(ren::core::Scene& scene, float delta_time);
void update_planet(ren::ecs::entities::Entity& entity, const Planet& planet, float delta_time);

} // namespace planetary_system

int main() {
    // Window initialization
    ren::core::Window window("Planetary System", 1980, 1080);
    ren::io::devices::Mouse::listen(window);
    ren::io::devices::Keyboard::listen(window);

    // Scene and renderer setup
    ren::core::Scene scene = planetary_system::create_system();
    ren::renderer::Renderer renderer;
    ren::renderer::CameraSystem camera_system;
    renderer.setRenderTarget(window.getGlfwWindow());

    // Main loop
    double last_time = glfwGetTime();
    while(window.isOpen()) {
        double current_time = glfwGetTime();
        float delta_time = static_cast<float>(current_time - last_time);
        last_time = current_time;

        planetary_system::update_system(scene, delta_time);
        camera_system.update(delta_time, renderer.getCamera());
        renderer.render(scene);
    }

    return 0;
}

namespace planetary_system {

std::vector<Planet> get_planets() {
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
            "Uranus", // Fixed typo in name
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

ren::core::Scene create_system() {
    ren::core::Scene scene;    
    auto& entity_manager = scene.getEntityManager();

    // Load shader
    ren::assets::AssetManager asset_manager;
    auto shader = asset_manager.loadShader(
        "assets\\shaders\\planetary_system\\planetary.vert", 
        "assets\\shaders\\planetary_system\\planetary.frag"
    );
    
    // Create planet template
    ren::ecs::entities::Entity planet_template;
    auto& component_manager = planet_template.getComponentManager();
    component_manager.add<ren::ecs::components::Transform>();
    component_manager.add<ren::ecs::components::meshes::Sphere>();

    // Create planet entities
    std::vector<Planet> planets = get_planets();
    auto& transform = component_manager.get<ren::ecs::components::Transform>().value().get();

    ren::ecs::components::shaders::Texture texture;
    texture.type = "texture_diffuse";

    for(const auto& planet_data : planets) {
        // Set planet texture
        texture.path = "assets\\textures\\planetary_system\\" + planet_data.name + ".jpg";
        texture.id = asset_manager.loadTextureFromImage(texture.path);
        component_manager.set(ren::ecs::components::MeshRenderer(shader, {texture}));
        
        // Set initial position
        transform.setPosition(planet_data.initial_position);
    
        // Add entity to scene
        planet_template.setId(planet_data.name);
        entity_manager.add(planet_template);
    }

    return scene;
}

void update_system(ren::core::Scene& scene, float delta_time) {
    auto& entity_manager = scene.getEntityManager();
    std::vector<Planet> planets = get_planets();
    
    for(const auto& planet_data : planets) {
        auto& planet_entity = entity_manager.get(planet_data.name).value().get();
        update_planet(planet_entity, planet_data, delta_time);
    }
}

void update_planet(ren::ecs::entities::Entity& entity, const Planet& planet, float delta_time) {
    auto& transform = entity.getComponentManager().get<ren::ecs::components::Transform>().value().get();
    auto position = transform.getPosition();
    auto right = glm::normalize(glm::cross(position, glm::vec3(0.0f, 1.0f, 0.0f)));

    // Handle planet rotation
    if(position != glm::vec3(0.0f)) {
        // Planets orbit around the sun
        transform.rotate(planet.relative_rotation_speed * delta_time, glm::normalize(glm::cross(position, right)));
    } else {
        // Sun rotates around itself
        transform.rotate(planet.relative_rotation_speed * delta_time, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Update planet position in orbit
    glm::mat4 rotation = glm::rotate(
        glm::mat4(1.0f), 
        glm::radians(planet.absolute_rotation_speed) * delta_time, 
        planet.rotation_axis
    );
    position = glm::vec3(rotation * glm::vec4(position, 1.0f));
    transform.setPosition(position);
}

} // namespace planetary_system