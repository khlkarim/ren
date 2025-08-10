#pragma once

#include <memory>
#include <vector>
#include <algorithm>
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

    void update(float dt, entities::EntityManager& entityManager);

private:
    std::vector<std::unique_ptr<System>> m_systems;
};

template<typename T>
void SystemManager::add() {
    m_systems.push_back(std::make_unique<T>());
}

template<typename T>
void SystemManager::set(const T& system) {
    m_systems.push_back(std::make_unique<T>(system));
}

template<typename T>
void SystemManager::remove() {
    m_systems.erase(
        std::remove_if(m_systems.begin(), m_systems.end(),
            [](const std::unique_ptr<System>& system) {
                return dynamic_cast<T*>(system.get()) != nullptr;
            }),
        m_systems.end()
    );
}

} 