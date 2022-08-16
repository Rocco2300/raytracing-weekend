#include "Camera.hpp"

#include <cmath>

Camera::Camera()
{
    lowerLeftCorner = Vec3(-2.f, 1.f, -1.f);
    horizontal = Vec3(4.f, 0.f, 0.f);
    vertical = Vec3(0.f, -2.f, 0.f);
    origin = Vec3(0.f, 0.f, 0.f);
}

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, f32 vFov, f32 aspect)
{
    Vec3 u, v, w;
    f32 theta = vFov * M_PI/180;
    f32 halfHeight = std::tan(theta/2);
    f32 halfWidth = aspect * halfHeight;

    origin = lookFrom;
    w = unitVector(lookFrom - lookAt);
    u = unitVector(cross(up, w));
    v = cross(w, u);

    lowerLeftCorner = Vec3(-halfWidth, halfHeight, -1);
    lowerLeftCorner = origin - halfWidth*u - halfHeight*v - w;
    horizontal = 2 * halfWidth * u;
    vertical = 2 * halfHeight * v;
}

Ray Camera::getRay(f32 u, f32 v)
{
    return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
}