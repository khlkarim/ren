#pragma once

#include <string>
#include "ecs/components/ComponentManager.hpp"

namespace ren::ecs::entities
{

class Entity
{
public:
    Entity() = default;
    Entity(const std::string& id);

    const std::string& getId() const;
    void setId(const std::string& id);

    components::ComponentManager& getComponentManager();
    const components::ComponentManager& getComponentManager() const;
    void setComponentManager(const components::ComponentManager& manager);

private:
    std::string id;
    components::ComponentManager componentManager;
};

}