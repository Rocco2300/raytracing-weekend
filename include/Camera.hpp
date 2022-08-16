#pragma once

#include "Ray.hpp"

class Camera
{
public:
    Vec3 u, v, w;
    Vec3 origin;
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;

    f32 lensRadius;

public:
    Camera();
    Camera(
        Vec3 lookFrom,
        Vec3 lookAt,
        Vec3 up,
        f32 vFov,
        f32 aspect,
        f32 aperture,
        f32 focusDist
    );

    Ray getRay(f32 s, f32 t);
};