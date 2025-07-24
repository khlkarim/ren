#include <core/Entity.hpp>
using ren::Entity;

Entity::Entity(const std::string& id)
{
    spdlog::info("Entity Constructor");
    this->id = id;
}

Entity::Entity(const Entity& other)
{
    this->id = other.id;

    for (const auto& comp : other.components) {
        if (comp) {
            spdlog::info("Component transfer ...");
            this->components.push_back(comp->clone());
        }
    }
}

Entity::~Entity()
{
    spdlog::info("Entity Destructor");
}

const std::string& Entity::getId() const
{
    return this->id;
}

void Entity::setId(const std::string& id)
{
    this->id = id;
}