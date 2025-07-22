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

namespace ren {

class Scene 
{
public:
    Scene();
    virtual ~Scene();

    void setCamera(const Camera& camera);
    const Camera& getCamera();

    const std::string& createEntity();

    template<typename T>
    void setComponent(const std::string& id, const T& component);

    template<typename T>
    std::optional<std::reference_wrapper<const T>> getComponent(const std::string& id) const;

    void render() const;

private:
    std::unique_ptr<Camera> camera;
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
};

}