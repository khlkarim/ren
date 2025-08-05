#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <type_traits>
#include <spdlog/spdlog.h>
#include <ren/utils/error_handler.hpp>
#include <ren/ecs/components/Component.hpp>

namespace ren::ecs::entities
{

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() {};

    Entity(const std::string& id);
    Entity(const Entity& other);

    Entity& operator=(const Entity& other);    

    const std::string& getId() const;
    void setId(const std::string& id);

    template<typename T>
    void setComponent(const T& component);

    template<typename T>
    std::optional<std::reference_wrapper<T>> getComponent();

    template<typename T>
    std::optional<std::reference_wrapper<const T>> getComponent() const;

    template<typename T>
    void deleteComponent();

    template<typename... ComponentTypes>
    bool has() const;

private:
    std::string id;
    std::vector<std::unique_ptr<ren::ecs::components::Component>> components;
};

}

template<typename T>
void ren::ecs::entities::Entity::setComponent(const T& component)
{
    if(!std::is_base_of<ren::ecs::components::Component, T>::value)
    {
        FATAL("{} must derive from Component", typeid(T).name());
    }
    
    for (auto& comp : components)
    {
        if (dynamic_cast<T*>(comp.get()))
        {
            comp = std::make_unique<T>(component);
            spdlog::warn(
                "Entity with id: {} already has component of type: {}: Component replaced.", 
                this->id, 
                typeid(T).name()
            );
            return;
        }
    }
    components.push_back(std::make_unique<T>(component));
}

template<typename T>
std::optional<std::reference_wrapper<T>> ren::ecs::entities::Entity::getComponent()
{
    if(!std::is_base_of<ren::ecs::components::Component, T>::value)
    {
        FATAL("{} must derive from Component", typeid(T).name());
    }

    for (const auto& comp : components)
    {
        if (auto ptr = dynamic_cast<T*>(comp.get()))
        {
            return *ptr;
        }
    }

    spdlog::warn("Entity with id: {} has no component of type: {}.", this->id, typeid(T).name());
    return std::nullopt;
}

template<typename T>
std::optional<std::reference_wrapper<const T>> ren::ecs::entities::Entity::getComponent() const
{
    if(!std::is_base_of<ren::ecs::components::Component, T>::value)
    {
        FATAL("{} must derive from Component", typeid(T).name());
    }

    for (const auto& comp : components)
    {
        if (auto ptr = dynamic_cast<T*>(comp.get()))
        {
            return *ptr;
        }
    }

    spdlog::warn("Entity with id: {} has no component of type: {}.", this->id, typeid(T).name());
    return std::nullopt;
}

template<typename T>
void ren::ecs::entities::Entity::deleteComponent()
{
    if(!std::is_base_of<ren::ecs::components::Component, T>::value)
    {
        FATAL("{} must derive from Component", typeid(T).name());
    }

    for(unsigned int i = 0; i<this->components.size(); i++)
    {
        if(dynamic_cast<T*>(this->components[i].get()))
        {
            this->components[i].reset(nullptr);
            this->components.erase(this->components.begin() + i);
            return;
        }
    }
}

template<typename... ComponentTypes>
bool ren::ecs::entities::Entity::has() const
{
    if(!(std::is_base_of<ren::ecs::components::Component, ComponentTypes>::value && ...))
    {
        FATAL("All types must derive from Component");
    }

    return (... && ([this]() {
        for (const auto& comp : components) {
            if (dynamic_cast<ComponentTypes*>(comp.get())) {
                return true;
            }
        }
        return false;
    }()));
}
