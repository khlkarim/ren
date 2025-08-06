#include "ecs/entities/Entity.hpp"
using ren::ecs::entities::Entity;

Entity::Entity(const std::string& id)
{
    this->id = id;
}

Entity::Entity(const Entity& other)
{
    this->id = other.id;

    for (const auto& comp : other.components) {
        if (comp) {
            this->components.push_back(comp->clone());
        }
    }
}

Entity& Entity::operator=(const Entity& other)
{
    if (this != &other) {
        this->id = other.id;
        
        this->components.clear();
        for (const auto& comp : other.components) {
            if (comp) {
                this->components.push_back(comp->clone());
            }
        }
    }
    return *this;
}

const std::string& Entity::getId() const
{
    return this->id;
}

void Entity::setId(const std::string& id)
{
    this->id = id;
}