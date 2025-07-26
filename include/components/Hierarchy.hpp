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
    void add(const Entity& entity);
    Entity& get(const std::string& id);
    void remove(const std::string& id);

    template<typename T>
    T& getComponent(const std::string& id);

    template<typename T>
    void setComponent(const std::string& id, const T& component);    
    
    template<typename... ComponentTypes>
    bool has(const std::string& id);
    
    template<typename... ComponentTypes>
    std::vector<std::string> getEntitiesWith() const;
    std::vector<std::string> getChildren() const;

    std::unique_ptr<Component> Hierarchy::clone() const;

private:
    std::unordered_map<std::string, Entity> children;
};

}

template<typename T>
void ren::components::Hierarchy::setComponent(const std::string& id, const T& component)
{
    if(this->children.find(id) == this->children.end())
    {
        FATAL("Entity with given id does not exist");
    }
    this->children[id].setComponent(component);
}

template<typename T>
T& ren::components::Hierarchy::getComponent(const std::string& id)
{
    if(this->children.find(id) == this->children.end())
    {
        FATAL("Entity with given id does not exist");
    }
    return this->children[id].getComponent<T>();
}

template<typename... ComponentTypes>
bool ren::components::Hierarchy::has(const std::string& id)
{
    return (this->children[id].has<ComponentTypes>() && ...);
}

template<typename... ComponentTypes>
std::vector<std::string> ren::components::Hierarchy::getEntitiesWith() const
{
    std::vector<std::string> result;
    for (const auto& [id, entity] : this->children)
    {
        if ((entity.has<ComponentTypes>() && ...))
        {
            result.push_back(id);
        }
    }
    return result;
}