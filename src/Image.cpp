#include "Image.hpp"

#include <cstdio>
#include <cstdlib>

bool Image::load(const std::string& path)
{
    FILE* file;
    file = std::fopen(path.c_str(), "rb");

    if (file == nullptr)
        return false;

    std::fread(&this->header, 14, 1, file);
    std::fread(&this->dibHeader, 40, 1, file);

    auto width = dibHeader.width;
    auto height = dibHeader.height;
    auto size = dibHeader.width * dibHeader.height;
    pixels = (Pixel*)std::malloc(sizeof(Pixel) * size);

    int padding;
    if ((sizeof(Pixel) * width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Pixel) * width) % 4;

    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        fread(pixels + offset, sizeof(Pixel) * width, 1, file);
        fseek(file, sizeof(Pixel) * padding, SEEK_CUR);
    }

    std::fclose(file);

    return true;
}
