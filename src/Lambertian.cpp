#include "Lambertian.hpp"

#include "Util.hpp"

Lambertian::Lambertian() : Material() { }

Lambertian::Lambertian(const Vec3 &albedo) : Material(albedo, .8f) { }

bool Lambertian::scatter(const Ray &rIn, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const
{
    Vec3 target = rec.p + rec.normal + randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}