#pragma once

#include <iostream>
#include "Types.hpp"

class Vec3
{
public:
    f32 x, y, z;
public:
    Vec3();
    Vec3(f32 x, f32 y, f32 z);

    Vec3 operator-() const;

    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(f32 t);
    Vec3& operator/=(f32 t);

    f32 length() const;
    f32 squaredLength() const;
    void makeUnitVec();

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
};

inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

inline Vec3 operator+(const Vec3& v1, f32 t)
{
    return {v1.x + t, v1.y + t, v1.z + t};
}

inline Vec3 operator-(const Vec3& v1, f32 t)
{
    return {v1.x + t, v1.y + t, v1.z + t};
}

inline f32 dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2)
{
    return
    {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

