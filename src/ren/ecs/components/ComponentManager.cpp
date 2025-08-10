#include "ecs/components/ComponentManager.hpp"

namespace ren::ecs::components {

ComponentManager::ComponentManager(const ComponentManager& other)
{
    for (const auto& component : other.m_components) {
        if (component) {
            m_components.push_back(component->clone());
        }
    }
}

ComponentManager& ComponentManager::operator=(const ComponentManager& other)
{
    if (this != &other) {
        m_components.clear();
        for (const auto& component : other.m_components) {
            if (component) {
                m_components.push_back(component->clone());
            }
        }
    }
    return *this;
}

}