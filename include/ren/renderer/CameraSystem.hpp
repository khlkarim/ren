#pragma once

namespace ren::renderer
{

class Camera;
class CameraSystem
{
public:
    CameraSystem();
    void update(float dt, Camera& camera);

private:
    void updatePosition(float dt, Camera& camera);
    void updateDirection(float dt, Camera& camera);

private:
    bool m_cursorLocked;
    bool m_firstMove = true;
    double m_lastX, m_lastY;
};

}