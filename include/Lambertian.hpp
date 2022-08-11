#pragma once

#include "Material.hpp"

class Lambertian : public Material
{
public:
    Vec3 albedo;

public:
    Lambertian(const Vec3& albedo);

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};
