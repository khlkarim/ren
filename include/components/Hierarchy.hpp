#pragma once

#include <string>
#include <vector>
#include <memory>
#include <core/Entity.hpp>
#include <utils/error_handler.hpp>
#include <components/Component.hpp>

namespace ren::components
{

class Hierarchy: public Component
{
public:
    Hierarchy() = default;
    Hierarchy(const Hierarchy& other);

    void add(const Entity& entity);
    Entity& get(const std::string& id);
    void remove(const std::string& id);

    template<typename T>
    T& getComponent(const std::string& id);

    template<typename T>
    void setComponent(const std::string& id, const T& component);    
    
    template<typename T>
    bool has(const std::string& id);
    
    template<typename... ComponentTypes>
    std::vector<std::string> getEntitiesWith() const;

    std::unique_ptr<Component> Hierarchy::clone() const;

private:
    std::unordered_map<std::string, std::unique_ptr<Entity>> children;
};

}

template<typename T>
void ren::components::Hierarchy::setComponent(const std::string& id, const T& component)
{
    if(this->children.find(id) == this->children.end())
    {
        fatal("Entity with given id does not exist");
    }
    this->children[id]->setComponent(component);
}

template<typename T>
T& ren::components::Hierarchy::getComponent(const std::string& id)
{
    if(this->children.find(id) == this->children.end())
    {
        fatal("Entity with given id does not exist");
    }
    return this->children[id]->getComponent<T>();
}

template<typename T>
bool ren::components::Hierarchy::has(const std::string& id)
{
    return this->children[id]->has<T>();
}

template<typename... ComponentTypes>
std::vector<std::string> ren::components::Hierarchy::getEntitiesWith() const
{
    std::vector<std::string> result;
    for (const auto& [id, entityPtr] : this->children)
    {
        if ((entityPtr->has<ComponentTypes>() && ...))
        {
            result.push_back(id);
        }
    }
    return result;
}