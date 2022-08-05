#pragma once

#include "Vec3.hpp"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
public:
    Ray();
    Ray(const Vec3& o, const Vec3& d);

    Vec3 at(f32 t) const;
};

