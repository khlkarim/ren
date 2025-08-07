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
    std::optional<std::reference_wrapper<const T>> getComponent(const std::string& id) const;

    template<typename T>
    void addComponent(const std::string& id); 

    template<typename T>
    void setComponent(const std::string& id, const T& component);  
    
    template<typename T>
    void removeComponent(const std::string& id);
    
    template<typename... ComponentTypes>
    bool has(const std::string& id) const;

    template<typename... ComponentTypes>
    std::vector<std::string> getEntitiesWith() const;

    std::vector<std::string> getEntityIds() const;

private:
    std::unordered_map<std::string, Entity> entities;
};

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

template<typename T>
std::optional<std::reference_wrapper<const T>> ren::ecs::entities::EntityManager::getComponent(const std::string& id) const
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

template<typename T>
void ren::ecs::entities::EntityManager::addComponent(const std::string& id)
{
    if(this->entities.find(id) == this->entities.end())
    {
        spdlog::warn("Cannot set component for Entity with id: {}: Entity does not exist.", id);
    }
    else
    {

        this->entities[id].getComponentManager().add<T>();
    }
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
void ren::ecs::entities::EntityManager::removeComponent(const std::string& id)
{
    if(this->entities.find(id) == this->entities.end())
    {
        spdlog::warn("Cannot set component for Entity with id: {}: Entity does not exist.", id);
    }
    else
    {

        this->entities[id].getComponentManager().remove<T>();
    }
}

template<typename... ComponentTypes>
bool ren::ecs::entities::EntityManager::has(const std::string& id) const
{
    auto it = this->entities.find(id);
    if (it == this->entities.end()) {
        spdlog::warn("Cannot check components for Entity with id: {}: Entity does not exist.", id);
        return false;
    }
    return (it->second.getComponentManager().has<ComponentTypes>() && ...);
}

template<typename... ComponentTypes>
std::vector<std::string> ren::ecs::entities::EntityManager::getEntitiesWith() const
{
    std::vector<std::string> result;
    for (const auto& [id, entity] : entities) {
        if ((this->has<ComponentTypes>(id) && ...)) {
            result.push_back(id);
        }
    }
    return result;
}