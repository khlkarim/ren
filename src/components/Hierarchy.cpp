#include <components/Hierarchy.hpp>
using ren::Entity;
using ren::components::Component;
using ren::components::Hierarchy;

void Hierarchy::add(const Entity& child) {
    if (children.find(child.getId()) != children.end()) {
        fatal("Entity with given id already exist");
    }
    children[child.getId()] = child;
}

Entity& Hierarchy::get(const std::string& id)
{
    if(this->children.find(id) == this->children.end())
    {
        fatal("Entity with given id does not exist");
    }
    return this->children[id];
}

void Hierarchy::remove(const std::string& id) {
    children.erase(id);
}

std::unique_ptr<Component> Hierarchy::clone() const
{
    return std::make_unique<Hierarchy>(*this);
}