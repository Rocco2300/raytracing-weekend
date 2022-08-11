#pragma once

#include <random>
#include <chrono>

#include "Vec3.hpp"
#include "Types.hpp"

inline f32 randFloat()
{
    static u64 timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::seed_seq ss{u32(timeSeed & 0xffffffff), u32(timeSeed >> 32)};

    static std::mt19937 rng(ss);
    static std::uniform_real_distribution<f32> unif(0, 1);

    return unif(rng);
}

inline Vec3 randomInUnitSphere()
{
    Vec3 p;
    do
    {
        p = 2.f*Vec3(randFloat(), randFloat(), randFloat()) - Vec3(1.f);
    } while (dot(p, p) >= 1.f);

    return p;
}

