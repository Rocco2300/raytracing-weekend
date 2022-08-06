#pragma once

#include "Hitable.hpp"

class Sphere : public Hitable
{
public:
    Vec3 center;
    f32 radius;
public:
    Sphere();
    Sphere(const Vec3& center, f32 r);
    virtual bool hit(const Ray& r, f32 tMin, f32 tMax, HitRecord& rec) const;
};


