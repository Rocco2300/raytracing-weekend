#include "Image.hpp"

#include <cstdio>
#include <cstdlib>

int Image::getPadding() const
{
    int padding;
    if ((sizeof(Pixel) * dibHeader.width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Pixel) * dibHeader.width) % 4;

    return padding;
}

void Image::save(const std::string& path)
{
    FILE *file;
    file = std::fopen(path.c_str(), "wb");

    auto width = dibHeader.width;
    auto height = dibHeader.height;

    int padding = getPadding();

    std::fwrite(&header, 14, 1, file);
    std::fwrite(&dibHeader, 40, 1, file);

    auto* pixel = (Pixel*)std::calloc(1, sizeof(Pixel));
    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        std::fwrite(pixels + offset, sizeof(Pixel) * width, 1, file);
        std::fwrite(pixel, sizeof(Pixel), padding, file);
    }

    fclose(file);
}

bool Image::load(const std::string& path)
{
    FILE *file;
    file = std::fopen(path.c_str(), "rb");

    if (file == nullptr)
        return false;

    std::fread(&this->header, 14, 1, file);
    std::fread(&this->dibHeader, 40, 1, file);

    auto width = dibHeader.width;
    auto height = dibHeader.height;
    auto size = dibHeader.width * dibHeader.height;
    pixels = (Pixel*)std::malloc(sizeof(Pixel) * size);

    int padding = getPadding();

    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        fread(pixels + offset, sizeof(Pixel) * width, 1, file);
        fseek(file, sizeof(Pixel) * padding, SEEK_CUR);
    }

    std::fclose(file);

    return true;
}
