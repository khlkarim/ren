#pragma once

#include <core/Camera.hpp>
#include <io/events/mouse/Moved.hpp>
#include <io/events/keyboard/KeyInput.hpp>

namespace ren::systems
{

class CameraSystem
{
public:
    CameraSystem();
    void update(const float dt, Camera& camera);

private:
    void updateDirection(const float dt, Camera& camera, const ren::io::events::mouse::Moved& event);
    void updatePosition(const float dt, Camera& camera, const ren::io::events::keyboard::KeyInput& event);

private:
    bool cursorLocked;
};

}