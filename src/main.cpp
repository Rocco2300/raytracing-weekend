#include <limits>
#include <random>
#include <chrono>

#include "Camera.hpp"
#include "HitableList.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Image.hpp"

Vec3 color(const Ray& r, Hitable *hitable)
{
    HitRecord rec;
    if (hitable->hit(r, 0.0, std::numeric_limits<float>::max(), rec))
    {
        return 0.5f*Vec3(rec.normal.x+1, rec.normal.y+1, rec.normal.z+1);
    }
    else
    {
        Vec3 unitDirection = unitVector(r.direction);
        f32 t = 0.5f * (unitDirection.y + 1.f);
        return (1.f - t)*Vec3(1.f, 1.f, 1.f) + t*Vec3(0.5f, 0.7f, 1.f);
    }
}

int main()
{
    u64 timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{u32(timeSeed & 0xffffffff), u32(timeSeed >> 32)};

    std::mt19937 rng(ss);
    std::uniform_real_distribution<f32> unif(0, 1);

    const int width = 800;
    const int height = width / 2;
    const int sampleCount = 100;

    Image img;
    img.create(width, height);

    Camera cam;

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5f);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Hitable *world = new HitableList(list, 2);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < sampleCount; s++)
            {
                f32 u = f32(x + unif(rng)) / f32(width);
                f32 v = f32(y + unif(rng)) / f32(height);

                Ray r = cam.getRay(u, v);
                col += color(r, world);
            }
            col /= float(sampleCount);

            img(x, y).r = int(255.99 * col.x);
            img(x, y).g = int(255.99 * col.y);
            img(x, y).b = int(255.99 * col.z);
        }
    }

    img.save("../render.bmp");
    return 0;
}