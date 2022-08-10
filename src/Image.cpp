#include "Image.hpp"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Image::Image(int width, int height) : header{}, dibHeader{}, pixels{nullptr}
{
    create(width, height);
}

Color& Image::operator[](int index)
{
    assert(index >= 0 && index < (dibHeader.width * dibHeader.height));

    return pixels[index];
}

Color& Image::operator()(int x, int y)
{
    assert(x >= 0 && x < dibHeader.width && y >= 0 && y < dibHeader.height);

    auto index = y * dibHeader.width + x;
    return pixels[index];
}

Color& Image::operator[](int index) const
{
    assert(index >= 0 && index < (dibHeader.width * dibHeader.height));

    return pixels[index];
}

Color& Image::operator()(int x, int y) const
{
    assert(x >= 0 && x < dibHeader.width && y >= 0 && y < dibHeader.height);

    auto index = y * dibHeader.width + x;
    return pixels[index];
}

u32 Image::getWidth() const
{
    return dibHeader.width;
}

u32 Image::getHeight() const
{
    return dibHeader.height;
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

    auto* pixel = (Color*)std::calloc(1, sizeof(Color));
    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        std::fwrite(pixels + offset, sizeof(Color) * width, 1, file);
        std::fwrite(pixel, sizeof(Color), padding, file);
    }

    fclose(file);
}

bool Image::load(const std::string& path)
{
    FILE *file;
    file = std::fopen(path.c_str(), "rb");

    if (file == nullptr)
    {
        std::cout << "Error opening file " << path << "!\n";
        return false;
    }

    std::fread(&this->header, 14, 1, file);
    std::fread(&this->dibHeader, 40, 1, file);

    auto width = dibHeader.width;
    auto height = dibHeader.height;
    auto size = dibHeader.width * dibHeader.height;
    pixels = (Color*)std::malloc(sizeof(Color) * size);

    if (pixels == nullptr)
    {
        std::cout << "Error allocating memory for file " << path << "!\n";
        return false;
    }

    int padding = getPadding();

    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;

        std::fread(pixels + offset, sizeof(char) * 3 * width, 1, file);
        std::fseek(file, sizeof(char) * 3 * padding, SEEK_CUR);
    }

    std::fclose(file);

    return true;
}

bool Image::create(int width, int height)
{
    pixels = (Color*)std::malloc(sizeof(Color) * (width * height));
    if (pixels == nullptr)
        return false;

    header.header = 0b100110101000010;

    int padding;
    if ((sizeof(Color) * width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Color) * width) % 4;

    header.size = 54 + ((width + padding) * height) * sizeof(Color);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.startingOffset = 54;

    dibHeader.headerSize = 40;
    dibHeader.width = width;
    dibHeader.height = height;
    dibHeader.colorPlanes = 1;
    dibHeader.bitsPerPixel = 24;
    dibHeader.compression = 0;
    dibHeader.imageSize = ((width + padding) * height) * sizeof(Color);
    dibHeader.horizontalResolution = 2835;
    dibHeader.verticalResolution = 2835;
    dibHeader.colorNumber = 0;
    dibHeader.importantColors = 0;

    return true;
}

u8 Image::getPadding() const
{
    u8 padding;
    if ((sizeof(Color) * dibHeader.width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Color) * dibHeader.width) % 4;

    return padding;
}
