#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <type_traits>
#include <spdlog/spdlog.h>
#include "utils/error_handler.hpp"
#include "ecs/components/Component.hpp"

namespace ren::ecs::components
{

class ComponentManager
{
public:
    ComponentManager() = default;
    virtual ~ComponentManager() {};
    ComponentManager(const ComponentManager& other);

    ComponentManager& operator=(const ComponentManager& other);    

    template<typename T>
    void add();

    template<typename T>
    void set(const T& component);

    template<typename T>
    std::optional<std::reference_wrapper<T>> get();

    template<typename T>
    std::optional<std::reference_wrapper<const T>> get() const;

    template<typename T>
    void remove();

    template<typename... ComponentTypes>
    bool has() const;

private:
    std::vector<std::unique_ptr<ren::ecs::components::Component>> components;
};

}

template<typename T>
void ren::ecs::components::ComponentManager::add()
{
    if(!std::is_base_of<ren::ecs::components::Component, T>::value)
    {
        FATAL("{} must derive from Component", typeid(T).name());
    }
    
    for (auto& comp : components)
    {
        if (dynamic_cast<T*>(comp.get()))
        {
            comp = std::make_unique<T>();
            spdlog::warn(
                "Entity already has component of type: {}: Component replaced.", 
                typeid(T).name()
            );
            return;
        }
    }
    components.push_back(std::make_unique<T>());
}

template<typename T>
void ren::ecs::components::ComponentManager::set(const T& component)
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
                "Entity already has component of type: {}: Component replaced.", 
                typeid(T).name()
            );
            return;
        }
    }
    components.push_back(std::make_unique<T>(component));
}

template<typename T>
std::optional<std::reference_wrapper<T>> ren::ecs::components::ComponentManager::get()
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

    spdlog::warn("Entity has no component of type: {}.", typeid(T).name());
    return std::nullopt;
}

template<typename T>
std::optional<std::reference_wrapper<const T>> ren::ecs::components::ComponentManager::get() const
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

    spdlog::warn("Entity has no component of type: {}.", typeid(T).name());
    return std::nullopt;
}

template<typename T>
void ren::ecs::components::ComponentManager::remove()
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
bool ren::ecs::components::ComponentManager::has() const
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
