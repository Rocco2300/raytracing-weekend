#include "Metal.hpp"

#include "Util.hpp"

Metal::Metal() : albedo{}, roughness{} { }

Metal::Metal(const Vec3& albedo, f32 roughness) : albedo{albedo}, roughness{roughness} { }

bool Metal::scatter(const Ray &rIn, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const
{
    Vec3 reflected = reflect(unitVector(rIn.direction), rec.normal);
    scattered = Ray(rec.p, reflected + roughness*randomInUnitSphere());
    attenuation = albedo;
    return (dot(scattered.direction, rec.normal) > 0);
}