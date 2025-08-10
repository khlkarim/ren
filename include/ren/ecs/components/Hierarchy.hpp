#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include "ecs/entities/Entity.hpp"
#include "ecs/components/Component.hpp"

namespace ren::ecs::components {

class Hierarchy : public Component {
public:
    void add(const entities::Entity& entity);

    std::optional<std::reference_wrapper<entities::Entity>> get(const std::string& id);
    std::optional<std::reference_wrapper<const entities::Entity>> get(const std::string& id) const;

    std::vector<std::string> getChildren() const;
    
    void remove(const std::string& id);
    
    std::unique_ptr<Component> clone() const override;

private:
    std::unordered_map<std::string, entities::Entity> m_children;
};

} 
