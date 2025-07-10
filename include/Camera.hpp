#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include "Transform.hpp"

class Camera 
{
public:
    void lookAt();
    
private:
    Transform transform;
};

#endif // CAMERA_HPP