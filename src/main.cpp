#include <limits>

#include "Camera.hpp"
#include "HitableList.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Util.hpp"
#include "Lambertian.hpp"

Vec3 color(const Ray& r, Hitable *hitable, int depth)
{
    HitRecord rec;
    if (hitable->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
    {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, hitable, depth + 1);
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
        return (1.f - t)*Vec3(1.f) + t*Vec3(0.5f, 0.7f, 1.f);
    }
}

int main()
{
    const int width = 800;
    const int height = width / 2;
    const int sampleCount = 100;

    Image img;
    img.create(width, height);

    Camera cam;

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5f, new Lambertian({0.8f, 0.3f, 0.3f}));
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian({0.8f, 0.8f, 0.f}));
    Hitable *world = new HitableList(list, 2);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < sampleCount; s++)
            {
                f32 u = f32(x + randFloat()) / f32(width);
                f32 v = f32(y + randFloat()) / f32(height);

                Ray r = cam.getRay(u, v);
                col += color(r, world, 0);
            }
            col /= float(sampleCount);
            col = Vec3(std::sqrt(col.x), std::sqrt(col.y), std::sqrt(col.z));

            img(x, y).r = col.x;
            img(x, y).g = col.y;
            img(x, y).b = col.z;
        }
    }

    img.save("../render.bmp");
    return 0;
}