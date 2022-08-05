#include "Vec3.hpp"

#include <cmath>

Vec3::Vec3()
    : x{}, y{}, z{} { }

Vec3::Vec3(f32 x, f32 y, f32 z)
    : x{x}, y{y}, z{z} { }

Vec3 Vec3::operator-() const
{
    return {x, -y, -z};
}

Vec3& Vec3::operator+=(const Vec3& v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
}

Vec3& Vec3::operator*=(f32 t)
{
    this->x *= t;
    this->y *= t;
    this->z *= t;
    return *this;
}

Vec3& Vec3::operator/=(f32 t)
{
    this->x /= t;
    this->y /= t;
    this->z /= t;
    return *this;
}

f32 Vec3::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

f32 Vec3::squaredLength() const
{
    return (x*x + y*y + z*z);
}

void Vec3::makeUnitVec()
{
    *this /= this->length();
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    os << v.x << " " << v.y << " " << v.z;
    return os;
}