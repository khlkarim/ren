#include "ecs/entities/EntityManager.hpp"

namespace ren::ecs::entities {

void EntityManager::add(const Entity& entity) {
    const std::string& id = entity.getId();
    
    if (id.empty()) {
        spdlog::warn("Entity has no id");
        return;
    }
    
    auto it = m_entities.find(id);
    if (it != m_entities.end()) {
        spdlog::warn("Entity with id: {} already existed: Entity replaced", id);
    }
    
    m_entities[id] = entity;
}

std::optional<std::reference_wrapper<Entity>> EntityManager::get(const std::string& id) {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        spdlog::warn("Entity with id: {} does not exist", id);
        return std::nullopt;
    }
    
    return it->second;
}

std::optional<std::reference_wrapper<const Entity>> EntityManager::get(const std::string& id) const {
    auto it = m_entities.find(id);
    if (it == m_entities.end()) {
        return std::nullopt;
    }
    
    return it->second;
}

std::vector<std::string> EntityManager::getEntityIds() const {
    std::vector<std::string> keys;
    keys.reserve(m_entities.size());
    
    for (const auto& [id, _] : m_entities) {
        keys.push_back(id);
    }
    
    return keys;
}

void EntityManager::remove(const std::string& id) {
    m_entities.erase(id);
}

} 