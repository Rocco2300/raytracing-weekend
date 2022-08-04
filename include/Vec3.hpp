#pragma once

#include "Types.hpp"

class Vec3
{
public:
    f32 x, y, z;
public:
    Vec3();
    Vec3(f32 x, f32 y, f32 z);

    const Vec3 operator-() const;

    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(f32 t);
    Vec3& operator/=(f32 t);

    f32 length() const;
    f32 squaredLength() const;
    void makeUnitVec();
};

inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator+(const Vec3& v1, f32 t)
{
    return Vec3(v1.x + t, v1.y + t, v1.z + t);
}

inline Vec3 operator-(const Vec3& v1, f32 t)
{
    return Vec3(v1.x + t, v1.y + t, v1.z + t);
}