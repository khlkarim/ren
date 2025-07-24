#include <components/Hierarchy.hpp>
using ren::components::Component;
using ren::components::Hierarchy;

void Hierarchy::setParent(const std::string& parentId) {
    parent = parentId;
}

const std::string& Hierarchy::getParent() const {
    return parent;
}

void Hierarchy::addChild(const std::string& childId) {
    if (std::find(children.begin(), children.end(), childId) == children.end()) {
        children.push_back(childId);
    }
}

void Hierarchy::removeChild(const std::string& childId) {
    auto it = std::find(children.begin(), children.end(), childId);
    if (it != children.end()) {
        children.erase(it);
    }
}

const std::vector<std::string>& Hierarchy::getChildren() const {
    return children;
}

std::unique_ptr<Component> Hierarchy::clone() const
{
    return std::make_unique<Hierarchy>(*this);
}