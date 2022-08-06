#pragma once

#include "Ray.hpp"

class Camera
{
public:
    Vec3 origin;
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
public:
    Camera();
    Ray getRay(f32 u, f32 v);
};