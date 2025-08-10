#pragma once

#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include "ecs/entities/Entity.hpp"
#include "utils/error_handler.hpp"
#include "ecs/components/Component.hpp"

namespace ren::ecs::entities {

class EntityManager {
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
    std::unordered_map<std::string, Entity> m_entities;
};

template<typename T>
std::optional<std::reference_wrapper<T>> EntityManager::getComponent(const std::string& id) {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Cannot get component for Entity with id: {}: Entity does not exist.", id);
        return std::nullopt;
    }
    return it->second.getComponentManager().get<T>();
}

template<typename T>
std::optional<std::reference_wrapper<const T>> EntityManager::getComponent(const std::string& id) const {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Cannot get component for Entity with id: {}: Entity does not exist.", id);
        return std::nullopt;
    }
    return it->second.getComponentManager().get<T>();
}

template<typename T>
void EntityManager::addComponent(const std::string& id) {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Cannot add component for Entity with id: {}: Entity does not exist.", id);
        return;
    }
    it->second.getComponentManager().add<T>();
}

template<typename T>
void EntityManager::setComponent(const std::string& id, const T& component) {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Cannot set component for Entity with id: {}: Entity does not exist.", id);
        return;
    }
    it->second.getComponentManager().set(component);
}

template<typename T>
void EntityManager::removeComponent(const std::string& id) {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Cannot remove component for Entity with id: {}: Entity does not exist.", id);
        return;
    }
    it->second.getComponentManager().remove<T>();
}

template<typename... ComponentTypes>
bool EntityManager::has(const std::string& id) const {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Cannot check components for Entity with id: {}: Entity does not exist.", id);
        return false;
    }
    return (it->second.getComponentManager().has<ComponentTypes>() && ...);
}

template<typename... ComponentTypes>
std::vector<std::string> EntityManager::getEntitiesWith() const {
    std::vector<std::string> result;
    for (const auto& [id, entity] : m_entities) {
        if ((entity.getComponentManager().has<ComponentTypes>() && ...)) {
            result.push_back(id);
        }
    }
    return result;
}

}