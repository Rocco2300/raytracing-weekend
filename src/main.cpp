#include <iostream>
#include <cmath>
#include <limits>

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
    const int width = 800;
    const int height = width / 2;

    Image img;
    img.create(width, height);

    Vec3 lowerLeftCorner(-2.f, 1.f, -1.f);
    Vec3 horizontal(4.f, 0.f, 0.f);
    Vec3 vertical(0.f, -2.f, 0.f);
    Vec3 origin(0.f, 0.f, 0.f);

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5f);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Hitable *world = new HitableList(list, 2);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            f32 u = x / float(width);
            f32 v = y / float(height);

            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical);
            Vec3 col = color(r, world);

            img(x, y).r = int(255.99 * col.x);
            img(x, y).g = int(255.99 * col.y);
            img(x, y).b = int(255.99 * col.z);
        }
    }

    img.save("../render.bmp");
    return 0;
}