#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <type_traits>
#include <spdlog/spdlog.h>
#include "utils/error_handler.hpp"
#include "ecs/components/Component.hpp"

namespace ren::ecs::components {

class ComponentManager {
public:
    ComponentManager() = default;
    virtual ~ComponentManager() = default;
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
    template<typename T>
    bool validateComponentType() const;

    template<typename T>
    bool findAndReplaceComponent(const T* replacement = nullptr);

    std::vector<std::unique_ptr<Component>> m_components;
};

template<typename T>
bool ComponentManager::validateComponentType() const {
    if (!std::is_base_of<Component, T>::value) {
        FATAL("{} must derive from Component", typeid(T).name());
        return false;
    }
    return true;
}

template<typename T>
bool ComponentManager::findAndReplaceComponent(const T* replacement) {
    for (auto& comp : m_components) {
        if (dynamic_cast<T*>(comp.get())) {
            if (replacement) {
                comp = std::make_unique<T>(*replacement);
            }
            return true;
        }
    }
    return false;
}

template<typename T>
void ComponentManager::add() {
    validateComponentType<T>();
    
    if (findAndReplaceComponent<T>()) {
        spdlog::warn("Entity already has component of type: {}: Component replaced.", 
                    typeid(T).name());
        return;
    }
    
    m_components.push_back(std::make_unique<T>());
}

template<typename T>
void ComponentManager::set(const T& component) {
    validateComponentType<T>();
    
    if (findAndReplaceComponent<T>(&component)) {
        spdlog::warn("Entity already has component of type: {}: Component replaced.", 
                    typeid(T).name());
        return;
    }
    
    m_components.push_back(std::make_unique<T>(component));
}

template<typename T>
std::optional<std::reference_wrapper<T>> ComponentManager::get() {
    validateComponentType<T>();

    for (const auto& comp : m_components) {
        if (auto ptr = dynamic_cast<T*>(comp.get())) {
            return *ptr;
        }
    }

    spdlog::warn("Entity has no component of type: {}.", typeid(T).name());
    return std::nullopt;
}

template<typename T>
std::optional<std::reference_wrapper<const T>> ComponentManager::get() const {
    validateComponentType<T>();

    for (const auto& comp : m_components) {
        if (auto ptr = dynamic_cast<const T*>(comp.get())) {
            return *ptr;
        }
    }

    spdlog::warn("Entity has no component of type: {}.", typeid(T).name());
    return std::nullopt;
}

template<typename T>
void ComponentManager::remove() {
    validateComponentType<T>();

    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        if (dynamic_cast<T*>(it->get())) {
            m_components.erase(it);
            return;
        }
    }
}

template<typename... ComponentTypes>
bool ComponentManager::has() const {
    if (!(std::is_base_of<Component, ComponentTypes>::value && ...)) {
        FATAL("All types must derive from Component");
    }

    return (... && ([this]() {
        for (const auto& comp : m_components) {
            if (dynamic_cast<ComponentTypes*>(comp.get())) {
                return true;
            }
        }
        return false;
    }()));
}

}