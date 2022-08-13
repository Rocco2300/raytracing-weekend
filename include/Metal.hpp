#pragma once

#include "Material.hpp"

class Metal : public Material
{
public:
    Metal();
    Metal(const Vec3& albedo, f32 roughness);

    bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};

