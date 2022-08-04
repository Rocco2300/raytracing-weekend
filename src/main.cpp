#include <iostream>

#include "Image.hpp"

int main()
{
    Image img;
    img.create(400, 400);

    for (int y = 0; y < img.getHeight(); y++)
    {
        for (int x = 0; x < img.getWidth(); x++)
        {
            f32 r = x / 400.f;
            f32 g = y / 400.f;
            f32 b = 0.2f;

            img(x, y).r = 255.99 * r;
            img(x, y).g = 255.99 * g;
            img(x, y).b = 255.99 * b;
        }
    }

    img.save("../uv.bmp");
    return 0;
}