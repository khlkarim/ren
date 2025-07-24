#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <type_traits>
#include <spdlog/spdlog.h>
#include <components/Component.hpp>

namespace ren
{

class Entity
{
public:
    Entity();
    virtual ~Entity();

    template<typename T>
    void setComponent(const T& component)
    {
        static_assert(std::is_base_of<ren::components::Component, T>::value, "T must derive from Component");
        
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
    T& getComponent()
    {
        for (const auto& comp : components)
        {
            if (auto ptr = dynamic_cast<T*>(comp.get()))
            {
                return *ptr;
            }
        }

        assert(0 && "Entity has no component of such type");
    }

    template<typename T>
    const T& getComponent() const
    {
        for (const auto& comp : components)
        {
            if (auto ptr = dynamic_cast<T*>(comp.get()))
            {
                return *ptr;
            }
        }

        assert(0 && "Entity has no component of such type");
    }
    
private:
    std::vector<std::unique_ptr<ren::components::Component>> components;
};

}
