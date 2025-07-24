#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include <core/Camera.hpp>
#include <core/Entity.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <systems/RenderSystem.hpp>

namespace ren {

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    void setCamera(const Camera& camera);
    std::optional<std::reference_wrapper<const Camera>> getCamera() const;

    std::string createEntity();

    template<typename T>
    void setComponent(const std::string& id, const T& component)
    {
        if (this->entities.find(id) != this->entities.end()) {
            this->entities[id]->setComponent(component);
            spdlog::info("Component added to Entity with id: {}", id);
        } else {
            spdlog::warn("Entity with id: {} does not exist", id);
        }
    }

    template<typename T>
    std::optional<std::reference_wrapper<const T>> getComponent(const std::string& id) const
    {
        if (this->entities.find(id) != this->entities.end()) {
            return this->entities[id]->getComponent<T>();
        } else {
            spdlog::warn("Entity with id: {} does not exist", id);
            return std::nullopt;
        }
    }

    void render() const;

private:
    std::unique_ptr<Camera> camera;
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
};

}