#include "Sphere.hpp"

#include <cmath>

Sphere::Sphere() : center{}, radius{} { }

Sphere::Sphere(const Vec3 &center, f32 r) : center{center}, radius{r} { }

bool Sphere::hit(const Ray& r, f32 tMin, f32 tMax, HitRecord& rec) const
{
    Vec3 oc = r.origin - center;
    f32 a = dot(r.direction, r.direction);
    f32 b = dot(oc, r.direction);
    f32 c = dot(oc, oc) - radius*radius;
    f32 discriminant = b*b - a*c;

    if (discriminant > 0)
    {
        f32 temp = (-b - std::sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }

    return false;
}