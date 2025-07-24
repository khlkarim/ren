#pragma once

#include <string>
#include <vector>
#include <memory>
#include <components/Component.hpp>

namespace ren::components
{

class Hierarchy: public Component
{
public:
    void setParent(const std::string& parentId);
    const std::string& getParent() const;

    void addChild(const std::string& childId);
    void removeChild(const std::string& childId);
    const std::vector<std::string>& getChildren() const;

    std::unique_ptr<Component> clone() const override;

private:
    std::string parent;
    std::vector<std::string> children;

};

}