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

    Camera& getCamera();
    void setCamera(const Camera& camera);

    std::string createEntity();
    void deleteEntity(const std::string& id);

    template<typename T>
    void setComponent(const std::string& id, const T& component)
    {
        assert(this->entities.find(id) != this->entities.end() && "Entity with given id does not exist");
        this->entities[id]->setComponent(component);
    }

    template<typename T>
    T& getComponent(const std::string& id)
    {
        assert(this->entities.find(id) != this->entities.end() && "Entity with given id does not exist");
        return this->entities[id]->getComponent<T>();
    }

    void render() const;

private:
    std::unique_ptr<Camera> camera;
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
};

}