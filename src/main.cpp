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
#include <algorithm>

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
            f32 receievedLight = std::max(dot(rec.normal, unitVector(light - rec.p)), 0.1f);
            if (hitable->hit(Ray(rec.p, light - rec.p), 0.001, F32MAX, rec))
                receievedLight = 0.1f;
            return receievedLight * attenuation * color(scattered, hitable, depth + 1);
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
    const int width = 800;
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

    for (int y = 0; y < height; y++)
    {
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

    img.save("../render.bmp");
    return 0;
}