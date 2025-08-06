#include "ecs/entities/Entity.hpp"
using ren::ecs::entities::Entity;
using ren::ecs::components::ComponentManager;

Entity::Entity(const std::string& id)
{
    this->id = id;
}

const std::string& Entity::getId() const
{
    return this->id;
}

void Entity::setId(const std::string& id)
{
    this->id = id;
}

ComponentManager& Entity::getComponentManager()
{
    return this->componentManager;
}

const ComponentManager& Entity::getComponentManager() const
{
    return this->componentManager;
}

void Entity::setComponentManager(const ComponentManager& manager)
{
    this->componentManager = manager;
}