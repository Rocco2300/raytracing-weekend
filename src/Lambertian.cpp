#include "Lambertian.hpp"

#include "Util.hpp"

Lambertian::Lambertian() : albedo{} { }

Lambertian::Lambertian(const Vec3 &albedo) : albedo{albedo} { }

bool Lambertian::scatter(const Ray &rIn, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const
{
    Vec3 target = rec.p + rec.normal + randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}