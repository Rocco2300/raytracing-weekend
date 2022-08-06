#include "Camera.hpp"

Camera::Camera()
{
    lowerLeftCorner = Vec3(-2.f, 1.f, -1.f);
    horizontal = Vec3(4.f, 0.f, 0.f);
    vertical = Vec3(0.f, -2.f, 0.f);
    origin = Vec3(0.f, 0.f, 0.f);
}

Ray Camera::getRay(f32 u, f32 v)
{
    return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
}