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
#include <utils/error_handler.hpp>

namespace ren {

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    Camera& getCamera();
    const Camera& getCamera() const;
    void setCamera(const Camera& camera);

    void remove(const std::string& id);
    void instantiate(const Entity& entity);
    Entity& getEntity(const std::string& id);

    template<typename T>
    void setComponent(const std::string& id, const T& component)
    {
        if(this->entities.find(id) == this->entities.end())
        {
            fatal("Entity with given id does not exist");
        }
        this->entities[id]->setComponent(component);
    }

    template<typename T>
    T& getComponent(const std::string& id)
    {
        if(this->entities.find(id) == this->entities.end())
        {
            fatal("Entity with given id does not exist");
        }
        return this->entities[id]->getComponent<T>();
    }

    template<typename T>
    bool has(const std::string& id)
    {
        return this->entities[id]->has<T>();
    }

    template<typename... ComponentTypes>
    std::vector<std::string> getEntitiesWith() const
    {
        std::vector<std::string> result;
        for (const auto& [id, entityPtr] : entities)
        {
            if ((entityPtr->has<ComponentTypes>() && ...))
            {
                result.push_back(id);
            }
        }
        return result;
    }

private:
    std::unique_ptr<Camera> camera;
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
};

}