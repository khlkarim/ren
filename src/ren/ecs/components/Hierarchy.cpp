#include "ecs/components/Hierarchy.hpp"
#include <spdlog/spdlog.h>

namespace ren::ecs::components {

void Hierarchy::add(const entities::Entity& child) {
    if (child.getId().empty()) {
        spdlog::warn("Entity has an empty id.");
        return;
    }
    
    if (this->m_children.find(child.getId()) != this->m_children.end()) {
        spdlog::warn("Entity with id: {} already existed: Entity replaced.", child.getId());
    }
    
    this->m_children[child.getId()] = child;
}

std::optional<std::reference_wrapper<entities::Entity>> Hierarchy::get(const std::string& id) {
    auto it = this->m_children.find(id);
    if (it == this->m_children.end()) {
        spdlog::warn("Entity with id: {} does not exist.", id);
        return std::nullopt;
    }
    
    return it->second;
}

std::optional<std::reference_wrapper<const entities::Entity>> Hierarchy::get(const std::string& id) const {
    auto it = this->m_children.find(id);
    if (it == this->m_children.end()) {
        spdlog::warn("Entity with id: {} does not exist.", id);
        return std::nullopt;
    }
    
    return it->second;
}

std::vector<std::string> Hierarchy::getChildren() const {
    std::vector<std::string> keys;
    keys.reserve(this->m_children.size());
    
    for (const auto& [id, _] : this->m_children) {
        keys.push_back(id);
    }
    
    return keys;
}

void Hierarchy::remove(const std::string& id) {
    this->m_children.erase(id);
}

std::unique_ptr<Component> Hierarchy::clone() const {
    return std::make_unique<Hierarchy>(*this);
}

} 
