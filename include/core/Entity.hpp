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
    void setComponent(const T& component);

    template<typename T>
    std::optional<std::reference_wrapper<const T>> getComponent() const;

private:
    std::vector<std::unique_ptr<ren::components::Component>> components;
};

}
