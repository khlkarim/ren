#pragma once

#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <spdlog/spdlog.h>
#include <utils/error_handler.hpp>
#include <components/Component.hpp>

namespace ren
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
    T& getComponent();

    template<typename T>
    const T& getComponent() const;

    template<typename T>
    void deleteComponent();

    template<typename... ComponentTypes>
    bool has() const;

private:
    std::string id;
    std::vector<std::unique_ptr<ren::components::Component>> components;
};

}

template<typename T>
void ren::Entity::setComponent(const T& component)
{
    if(!std::is_base_of<ren::components::Component, T>::value)
    {
        FATAL("T must derive from Component");
    }
    
    for (auto& comp : components)
    {
        if (dynamic_cast<T*>(comp.get()))
        {
            comp = std::make_unique<T>(component);
            return;
        }
    }
    components.push_back(std::make_unique<T>(component));
}

template<typename T>
T& ren::Entity::getComponent()
{
    for (const auto& comp : components)
    {
        if (auto ptr = dynamic_cast<T*>(comp.get()))
        {
            return *ptr;
        }
    }

    FATAL("Entity has no component of such type: {}", typeid(T).name());
}

template<typename T>
const T& ren::Entity::getComponent() const
{
    for (const auto& comp : components)
    {
        if (auto ptr = dynamic_cast<T*>(comp.get()))
        {
            return *ptr;
        }
    }

    FATAL("Entity has no component of such type");
}

template<typename T>
void ren::Entity::deleteComponent()
{
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
bool ren::Entity::has() const
{
    return (... && ([this]() {
        for (const auto& comp : components) {
            if (dynamic_cast<ComponentTypes*>(comp.get())) {
                return true;
            }
        }
        return false;
    }()));
}
