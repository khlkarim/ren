#pragma once

#include <string>
#include <vector>
#include <optional>
#include <spdlog/spdlog.h>
#include "ecs/entities/Entity.hpp"
#include "utils/error_handler.hpp"
#include "ecs/components/Component.hpp"

namespace ren::ecs::entities
{

class EntityManager
{
public:
    void add(const Entity& entity);
    std::optional<std::reference_wrapper<Entity>> get(const std::string& id);
    std::optional<std::reference_wrapper<const Entity>> get(const std::string& id) const;
    void remove(const std::string& id);

    template<typename T>
    std::optional<std::reference_wrapper<T>> getComponent(const std::string& id);

    template<typename T>
    void setComponent(const std::string& id, const T& component);    
    
    template<typename... ComponentTypes>
    bool has(const std::string& id);

    std::vector<std::string> getEntityIds() const;

private:
    std::unordered_map<std::string, Entity> entities;
};

}

template<typename T>
void ren::ecs::entities::EntityManager::setComponent(const std::string& id, const T& component)
{
    if(this->entities.find(id) == this->entities.end())
    {
        spdlog::warn("Cannot set component for Entity with id: {}: Entity does not exist.", id);
    }
    else
    {

        this->entities[id].getComponentManager().set(component);
    }
}

template<typename T>
std::optional<std::reference_wrapper<T>> ren::ecs::entities::EntityManager::getComponent(const std::string& id)
{
    if(this->entities.find(id) == this->entities.end())
    {
        spdlog::warn("Cannot get component for Entity with id: {}: Entity does not exist.", id);
        return std::nullopt;
    }
    else 
    {
        return this->entities[id].getComponentManager().get<T>();
    }
}

template<typename... ComponentTypes>
bool ren::ecs::entities::EntityManager::has(const std::string& id)
{
    return (this->entities[id].getComponentManager().has<ComponentTypes>() && ...);
}