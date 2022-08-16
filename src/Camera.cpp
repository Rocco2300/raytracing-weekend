#include "Camera.hpp"

#include <cmath>

Camera::Camera()
{
    lowerLeftCorner = Vec3(-2.f, 1.f, -1.f);
    horizontal = Vec3(4.f, 0.f, 0.f);
    vertical = Vec3(0.f, -2.f, 0.f);
    origin = Vec3(0.f, 0.f, 0.f);
}

Camera::Camera(f32 vFov, f32 aspect)
{
    f32 theta = vFov * M_PI/180;
    f32 halfHeight = std::tan(theta/2);
    f32 halfWidth = aspect * halfHeight;

    lowerLeftCorner = Vec3(-halfWidth, halfHeight, -1);
    horizontal = Vec3(2*halfWidth, 0.f, 0.f);
    vertical = Vec3(0.f, -2*halfHeight, 0.f);
    origin = (0.f, 0.f, 0.f);
}

Ray Camera::getRay(f32 u, f32 v)
{
    return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
}