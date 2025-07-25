#include <core/Entity.hpp>
using ren::Entity;

Entity::Entity()
{
    spdlog::info("Entity Constructor");
}

Entity::~Entity()
{
    spdlog::info("Entity Destructor");
}

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

Entity& Entity::operator=(const Entity& other)
{
    if (this != &other) {
        this->id = other.id;
        
        this->components.clear();
        for (const auto& comp : other.components) {
            if (comp) {
                spdlog::info("Component transfer ...");
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