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
#include <iostream>
#include <algorithm>

Color color(const Ray& r, Hitable *hitable, int depth)
{
    const f32 F32MAX = std::numeric_limits<float>::max();
    const Vec3 light(2.f, 2.f, 3.f);

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

Hitable* randomScene()
{
    int n = 500;
    Hitable** list = new Hitable*[n+1];
    list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(.5f, .5f, .5f)));
    int i = 1;

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++) {
            f32 matChosen = randFloat();
            Vec3 center(a + 0.9f * randFloat(), 0.2f, b + 0.9f * randFloat());

            if ((center - Vec3(4, 0.2f, 0)).length() > 0.9f)
            {
                if (matChosen < 0.8f)
                {
                    list[i++] = new Sphere(center, 0.2f,
                        new Lambertian(Vec3(randFloat()*randFloat(), randFloat()*randFloat(), randFloat()*randFloat())));
                }
                else if (matChosen < 0.95f)
                {
                    list[i++] = new Sphere(center, 0.2f,
                       new Metal(Vec3(.5f*(1 + randFloat()), .5f*(1 + randFloat()), .5f*(1 + randFloat())), .5f*randFloat()));
                }
            }
        }
    }

    list[i++] = new Sphere({0, .5f, -1}, .5f, new Lambertian({0.8f, 0.3f, 0.3f}));
    list[i++] = new Sphere({1, .5f, -1}, .5f, new Metal({0.8f, 0.6f, 0.2f}, 0.2f));
    list[i++] = new Sphere({-1, .5f, -1}, .5f, new Metal({0.8f, 0.8f, 0.8f}, 0.f));

    return new HitableList(list, i);
}

int main()
{
    const int width = 400;
    const int height = width / 2;
    const int sampleCount = 100;

    Image img;
    img.create(width, height);

    Vec3 up(0, -1, 0);
    Vec3 lookAt(-.5f, .5f, -1);
    Vec3 lookFrom(-3, 2, 2);

    f32 aperture = 0.1f;
    f32 distToFocus = 5.f;

    Camera cam(lookFrom, lookAt, up, 30, (f32)width / (f32)height, aperture, distToFocus);

    Hitable* world = randomScene();

    loadingBarInit();
    for (int y = 0; y <= height; y++)
    {
        loadingBarPrint(y, height);

        if (y == height)
            break;

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
    loadingBarCleanup();

    img.save("../render.bmp");
    return 0;
}