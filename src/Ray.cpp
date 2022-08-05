#include "Ray.hpp"

Ray::Ray() : origin{}, direction{} { }

Ray::Ray(const Vec3 &o, const Vec3 &d) : origin{o}, direction{d} { }

Vec3 Ray::at(f32 t) const
{
    return origin + t*direction;
}