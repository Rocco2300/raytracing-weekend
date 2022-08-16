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
    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, f32 vFov, f32 aspect);

    Ray getRay(f32 u, f32 v);
};