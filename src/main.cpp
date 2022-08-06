#include <iostream>

#include "Ray.hpp"
#include "Image.hpp"

bool hitSphere(const Vec3& center, f32 radius, const Ray& r)
{
    Vec3 oc = r.origin - center;
    f32 a = dot(r.direction, r.direction);
    f32 b = 2.f * dot(oc, r.direction);
    f32 c = dot(oc, oc) - radius*radius;
    f32 discriminant = b*b - 4*a*c;

    return (discriminant > 0);
}

Vec3 color(const Ray& r)
{
    if (hitSphere(Vec3(0, 0, -1), 0.5f, r))
        return {1, 0, 0};

    Vec3 unitDirection = unitVector(r.direction);
    f32 t = 0.5f * (unitDirection.y + 1.f);
    return (1.f - t)*Vec3(1.f, 1.f, 1.f) + t*Vec3(0.5f, 0.7f, 1.f);
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

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            f32 u = x / float(width);
            f32 v = y / float(height);

            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical);
            Vec3 col = color(r);

            img(x, y).r = int(255.99 * col.x);
            img(x, y).g = int(255.99 * col.y);
            img(x, y).b = int(255.99 * col.z);
        }
    }

    img.save("../render.bmp");
    return 0;
}