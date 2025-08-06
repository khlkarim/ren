#include "ecs/components/ComponentManager.hpp"
using ren::ecs::components::ComponentManager;

ComponentManager::ComponentManager(const ComponentManager& other)
{
    for (const auto& comp : other.components) {
        if (comp) {
            this->components.push_back(comp->clone());
        }
    }
}

ComponentManager& ComponentManager::operator=(const ComponentManager& other)
{
    if (this != &other) {
        this->components.clear();
        for (const auto& comp : other.components) {
            if (comp) {
                this->components.push_back(comp->clone());
            }
        }
    }
    return *this;
}