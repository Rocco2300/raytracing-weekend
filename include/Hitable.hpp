#pragma once

#include "Ray.hpp"

class Material;

struct HitRecord
{
    f32 t;
    Vec3 p;
    Vec3 normal;
    Material* matPtr;
};

class Hitable
{
public:
    virtual bool hit(const Ray& r, f32 tMin, f32 tMax, HitRecord& rec) const = 0;
};

