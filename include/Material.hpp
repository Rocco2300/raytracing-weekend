#pragma once

#include "Hitable.hpp"

class Material
{
public:
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};
