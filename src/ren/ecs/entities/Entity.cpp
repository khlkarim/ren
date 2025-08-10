#include "ecs/entities/Entity.hpp"
using ren::ecs::entities::Entity;
using ren::ecs::components::ComponentManager;

Entity::Entity(const std::string& id)
{
    this->m_id = id;
}

const std::string& Entity::getId() const
{
    return this->m_id;
}

void Entity::setId(const std::string& id)
{
    this->m_id = id;
}

ComponentManager& Entity::getComponentManager()
{
    return this->m_componentManager;
}

const ComponentManager& Entity::getComponentManager() const
{
    return this->m_componentManager;
}

void Entity::setComponentManager(const ComponentManager& manager)
{
    this->m_componentManager = manager;
}