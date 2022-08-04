#include <iostream>

#include "Image.hpp"

int main()
{
    Image img;
    img.load("../lena.bmp");

    for (int i = 0; i < img.getHeight(); i++)
    {
        for (int j = 0; j < img.getWidth(); j++)
        {
            int r = img(j, i).r;
            int g = img(j, i).g;
            int b = img(j, i).b;
            int value = (r + b + g) / 3;

            img(j, i).r = value;
            img(j, i).g = value;
            img(j, i).b = value;
        }
    }

    img.save("../grayscale.bmp");
    return 0;
}