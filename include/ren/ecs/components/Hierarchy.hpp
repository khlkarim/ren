#pragma once

#include <string>
#include <vector>
#include <optional>
#include <spdlog/spdlog.h>
#include "ecs/entities/Entity.hpp"
#include "utils/error_handler.hpp"
#include "ecs/components/Component.hpp"

namespace ren::ecs::components
{

class Hierarchy: public Component
{
public:
    void add(const entities::Entity& entity);
    std::optional<std::reference_wrapper<entities::Entity>> get(const std::string& id);
    std::optional<std::reference_wrapper<const entities::Entity>> get(const std::string& id) const;
    void remove(const std::string& id);

    template<typename T>
    std::optional<std::reference_wrapper<T>> getComponent(const std::string& id);

    template<typename T>
    void setComponent(const std::string& id, const T& component);    
    
    template<typename... ComponentTypes>
    bool has(const std::string& id);
    
    std::vector<std::string> getChildren() const;
    std::unique_ptr<Component> Hierarchy::clone() const;

private:
    std::unordered_map<std::string, entities::Entity> children;
};

}

template<typename T>
void ren::ecs::components::Hierarchy::setComponent(const std::string& id, const T& component)
{
    if(this->children.find(id) == this->children.end())
    {
        spdlog::warn("Cannot set component for Entity with id: {}: Entity does not exist.", id);
    }
    else
    {
        this->children[id].setComponent(component);
    }
}

template<typename T>
std::optional<std::reference_wrapper<T>> ren::ecs::components::Hierarchy::getComponent(const std::string& id)
{
    if(this->children.find(id) == this->children.end())
    {
        spdlog::warn("Cannot get component for Entity with id: {}: Entity does not exist.", id);
        return std::nullopt;
    }
    else 
    {
        return this->children[id].getComponent<T>();
    }
}

template<typename... ComponentTypes>
bool ren::ecs::components::Hierarchy::has(const std::string& id)
{
    return (this->children[id].has<ComponentTypes>() && ...);
}