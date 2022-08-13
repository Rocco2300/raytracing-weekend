#pragma once

#include "Hitable.hpp"

class Material
{
public:
    Color albedo;
    f32 roughness;

public:
    Material()
        : albedo{}, roughness{} { }
    Material(const Color& albedo, f32 roughness)
        : albedo{albedo}, roughness{roughness} { }
    virtual ~Material() = default;

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};
