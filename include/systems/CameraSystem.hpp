#pragma once

#include <systems/System.hpp>

namespace ren
{
    class Camera;
}

namespace ren::systems
{

class CameraSystem: public System
{
public:
    CameraSystem();
    void update(const float dt, Scene& scene);
    std::unique_ptr<System> clone() const;

private:
    void updatePosition(const float dt, Camera& camera);
    void updateDirection(const float dt, Camera& camera);

private:
    bool cursorLocked;
};

}