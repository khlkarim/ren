#pragma once

#include <vector>
#include <memory>
#include "ecs/systems/System.hpp"

namespace ren::ecs::systems 
{

class SystemManager 
{
public:
    SystemManager() = default;
    SystemManager(const SystemManager&);
    SystemManager& operator=(const SystemManager&);
    virtual ~SystemManager() = default;

    template<typename T>
    void add();

    template<typename T>
    void set(const T& system);

    template<typename T>
    void remove();

    void update(const float dt, entities::EntityManager& entityManager);

private:
    std::vector<std::unique_ptr<System>> systems;
};

}

template<typename T>
void ren::ecs::systems::SystemManager::add() {
    systems.push_back(std::make_unique<T>());
}

template<typename T>
void ren::ecs::systems::SystemManager::set(const T& system) {
    systems.push_back(std::make_unique<T>(system));
}

template<typename T>
void ren::ecs::systems::SystemManager::remove() {
    systems.erase(
        std::remove_if(systems.begin(), systems.end(),
            [](const std::unique_ptr<systems::System>& sys) {
                return dynamic_cast<T*>(sys.get()) != nullptr;
            }),
        systems.end()
    );
}