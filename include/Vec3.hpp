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
    Vec3& operator*=(const f32 t);
    Vec3& operator/=(const f32 t);
    Vec3 operator+(const Vec3& v);
    Vec3 operator-(const Vec3& v);

    f32 length() const;
    f32 squaredLength() const;
    void makeUnitVec();
};
