#pragma once

namespace ren::renderer
{

class Camera;
class CameraSystem
{
public:
    CameraSystem();
    void update(const float dt, renderer::Camera& camera);

private:
    void updatePosition(const float dt, renderer::Camera& camera);
    void updateDirection(const float dt, renderer::Camera& camera);

private:
    bool cursorLocked;
};

}