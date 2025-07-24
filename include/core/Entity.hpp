#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
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
    std::optional<std::reference_wrapper<const T>> getComponent() const
    {
        for (const auto& comp : components)
        {
            if (auto ptr = dynamic_cast<const T*>(comp.get()))
            {
                return std::cref(*ptr);
            }
        }
        return std::nullopt;
    }
    
private:
    std::vector<std::unique_ptr<ren::components::Component>> components;
};

}
