#pragma once

#include <random>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "Vec3.hpp"
#include "Types.hpp"

inline void loadingBarInit()
{
    std::ostream::sync_with_stdio(false);
    std::cout
        << "\e[?25l"
        << std::fixed
        << std::setprecision(2)
        << std::left
        << std::setfill((char)179);
}

inline void loadingBarPrint(int progress, int total)
{
    std::string white = "\u001b[37;1m";
    std::string green = "\u001b[32;1m";
    std::string yellow = "\u001b[33;1m";
    std::string loadingBar;

    f32 percent = 100 * ((float)progress / total);

    loadingBar.resize(percent / 2);
    std::fill(loadingBar.begin(), loadingBar.end(), (char)219);

    std::cout
        << '\r'
        << white
        << "Scanlines "
        << (progress == total ? green : yellow)
        << (char)179
        << std::setw(100 / 2)
        << std::setfill((char)178)
        << loadingBar
        << std::setw(1)
        << (char)179
        << ' '
        << white
        << percent
        << "%"
        << std::flush;
}

inline void loadingBarCleanup()
{
    std::string reset = "\u001b[0m";
    std::cout << "\e[?25h" << reset;
    std::ostream::sync_with_stdio(true);
}

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

inline Vec3 randomInUnitDisc()
{
    Vec3 p;

    do
    {
        p = 2.f * Vec3(randFloat(), randFloat(), 0) - Vec3(1, 1, 0);
    } while (dot(p, p) >= 1.f);

    return p;
}
