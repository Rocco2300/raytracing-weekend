#pragma once

#include "Material.hpp"

class Lambertian : public Material
{
public:
    Lambertian();
    Lambertian(const Vec3& albedo);

    bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};
