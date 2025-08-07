#include "ecs/entities/EntityManager.hpp"
using ren::ecs::entities::Entity;
using ren::ecs::entities::EntityManager;

void EntityManager::add(const Entity& entity) {
    if(entity.getId().length() == 0)
    {
        spdlog::warn("Entity has an no id.");
    }
    if (this->entities.find(entity.getId()) != this->entities.end()) {
        spdlog::warn("Entity with id: {} already existed: Entity replaced.", entity.getId());
    }
    this->entities[entity.getId()] = entity;
}

std::optional<std::reference_wrapper<Entity>> EntityManager::get(const std::string& id)
{
    if(this->entities.find(id) == this->entities.end())
    {
        spdlog::warn("Entity with id: {} does not exist.", id);
        return std::nullopt;
    }
    else
    {
        return this->entities.at(id);
    }
}

std::optional<std::reference_wrapper<const Entity>> EntityManager::get(const std::string& id) const
{
    if(this->entities.find(id) == this->entities.end())
    {
        return std::nullopt;
    }
    else
    {
        return this->entities.at(id);
    }
}

std::vector<std::string> EntityManager::getEntityIds() const
{
    std::vector<std::string> keys;

    for (const auto& pair : this->entities) {
        keys.push_back(pair.first);
    }

    return keys;
}

void EntityManager::remove(const std::string& id) {
    this->entities.erase(id);
}