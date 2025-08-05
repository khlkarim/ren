#include <ren/ecs/components/Hierarchy.hpp>
using ren::ecs::entities::Entity;
using ren::ecs::components::Component;
using ren::ecs::components::Hierarchy;

void Hierarchy::add(const Entity& child) {
    if(child.getId().length() == 0)
    {
        spdlog::warn("Entity has an empty id.");
    }
    if (children.find(child.getId()) != children.end()) {
        spdlog::warn("Entity with id: {} already existed: Entity replaced.", child.getId());
    }
    children[child.getId()] = child;
}

std::optional<std::reference_wrapper<Entity>> Hierarchy::get(const std::string& id)
{
    if(this->children.find(id) == this->children.end())
    {
        spdlog::warn("Entity with id: {} does not exist.", id);
        return std::nullopt;
    }
    else
    {
        return this->children.at(id);
    }
}

std::optional<std::reference_wrapper<const Entity>> Hierarchy::get(const std::string& id) const
{
    if(this->children.find(id) == this->children.end())
    {
        spdlog::warn("Entity with id: {} does not exist.", id);
        return std::nullopt;
    }
    else
    {
        return this->children.at(id);
    }
}

std::vector<std::string> Hierarchy::getChildren() const
{
    std::vector<std::string> keys;

    for (const auto& pair : children) {
        keys.push_back(pair.first);
    }

    return keys;
}

void Hierarchy::remove(const std::string& id) {
    children.erase(id);
}

std::unique_ptr<Component> Hierarchy::clone() const
{
    return std::make_unique<Hierarchy>(*this);
}