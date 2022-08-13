#include <limits>

#include "Camera.hpp"
#include "HitableList.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Util.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <algorithm>

void set_cursor(bool visible){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

Color color(const Ray& r, Hitable *hitable, int depth)
{
    const f32 F32MAX = std::numeric_limits<float>::max();
    const Vec3 light(2.f, 2.f, 0.f);

    HitRecord rec;
    if (hitable->hit(r, 0.001f, F32MAX, rec))
    {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 100 && rec.matPtr->scatter(r, rec, attenuation, scattered))
        {
            Vec3 L = unitVector(light - rec.p);
            Vec3 N = rec.normal;

            f32 illumination = std::max(dot(N, L), 0.1f);
            if (hitable->hit(Ray(rec.p, L), 0.001, F32MAX, rec))
                illumination = 0.1f;
            return illumination * attenuation * color(scattered, hitable, depth + 1);
        }
        else
        {
            return {0.f, 0.f, 0.f};
        }
    }
    else
    {
        Vec3 unitDirection = unitVector(r.direction);
        f32 t = 0.5f * (unitDirection.y + 1.f);
        return (1.f - t)*Color(1.f) + t*Color(0.5f, 0.7f, 1.f);
    }
}

int main()
{
    const int width = 200;
    const int height = width / 2;
    const int sampleCount = 100;

    Image img;
    img.create(width, height);

    Camera cam;

    Hitable *list[4];
    list[0] = new Sphere({0, 0, -1}, 0.5f, new Lambertian({0.8f, 0.3f, 0.3f}));
    list[1] = new Sphere({0, -100.5, -1}, 100, new Lambertian({0.8f, 0.8f, 0.f}));
    list[2] = new Sphere({1, 0, -1}, 0.5f, new Metal({0.8f, 0.6f, 0.2f}, 0.1f));
    list[3] = new Sphere({{-1, 0, -1}, 0.5f, new Metal({0.8f, 0.8f, 0.8f}, 0.5f)});
    Hitable *world = new HitableList(list, 4);

//    set_cursor(false);
    std::ostream::sync_with_stdio(false);
    std::cout << "\e[?25l" << std::fixed << std::setprecision(2) << std::left << std::setfill((char)179);
    for (int y = 0; y <= height; y++)
    {
        f32 percent = 100 * ((float)y / height);

        std::string empty;
        std::string filled;

        filled.resize(percent / 2);
        std::fill(filled.begin(), filled.end(), (char)219);


        if (y == height)
        {
            std::cout << '\r' << "\u001b[32;1m" << (char)179 << std::setw(100 / 2) << std::setfill((char)178) << filled << std::setw(1) << (char)179 << percent << "%" << "\u001b[0m" << std::flush;
            break;
        }

        std::cout << '\r' << "\u001b[33m" << (char)179 << std::setw(100 / 2) << std::setfill((char)178) << filled << std::setw(1) << (char)179 << percent << "%" << std::flush;

        for (int x = 0; x < width; x++)
        {
            Color col(0, 0, 0);
            for (int s = 0; s < sampleCount; s++)
            {
                f32 u = f32(x + randFloat()) / f32(width);
                f32 v = f32(y + randFloat()) / f32(height);

                Ray r = cam.getRay(u, v);
                col += color(r, world, 0);
            }
            col /= float(sampleCount);
            col = Color(std::sqrt(col.r), std::sqrt(col.g), std::sqrt(col.b));

            img(x, y).r = col.x;
            img(x, y).g = col.y;
            img(x, y).b = col.z;
        }
    }
//    set_cursor(true);

    img.save("../render.bmp");
    return 0;
}