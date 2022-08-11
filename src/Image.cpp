#include "Image.hpp"

#include <cstdio>
#include <cstdlib>
#include <cassert>

Image::Image(int width, int height) : header{}, dibHeader{}, pixels{nullptr}
{
    create(width, height);
}

Image::~Image()
{
    std::free(pixels);
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

    auto data = transformToChar(pixels);

    auto* pixel = (Color8*)std::calloc(1, sizeof(Color8));
    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        std::fwrite(data + offset, sizeof(Color8) * width, 1, file);
        std::fwrite(pixel, sizeof(Color8), padding, file);
    }


    std::fclose(file);
    std::free(data);
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

    auto data = (Color8*)std::malloc(sizeof(Color8) * size);
    pixels = (Color*)std::malloc(sizeof(Color) * size);

    if (pixels == nullptr || data == nullptr)
    {
        std::cout << "Error allocating memory for file " << path << "!\n";
        return false;
    }

    int padding = getPadding();

    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;

        std::fread(data + offset, sizeof(Color8) * width, 1, file);
        std::fseek(file, sizeof(Color8) * padding, SEEK_CUR);
    }

    pixels = transformToFloat(data);
    std::fclose(file);
    std::free(data);
    return true;
}

bool Image::create(int width, int height)
{
    pixels = (Color*)std::malloc(sizeof(Color) * (width * height));
    if (pixels == nullptr)
        return false;

    header.header = 0b100110101000010;

    int padding;
    if ((sizeof(Color8) * width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Color8) * width) % 4;

    header.size = 54 + ((width + padding) * height) * sizeof(Color8);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.startingOffset = 54;

    dibHeader.headerSize = 40;
    dibHeader.width = width;
    dibHeader.height = height;
    dibHeader.colorPlanes = 1;
    dibHeader.bitsPerPixel = 24;
    dibHeader.compression = 0;
    dibHeader.imageSize = ((width + padding) * height) * sizeof(Color8);
    dibHeader.horizontalResolution = 2835;
    dibHeader.verticalResolution = 2835;
    dibHeader.colorNumber = 0;
    dibHeader.importantColors = 0;

    return true;
}

u8 Image::getPadding() const
{
    u8 padding;
    if ((sizeof(Color8) * dibHeader.width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Color8) * dibHeader.width) % 4;

    return padding;
}

Color* Image::transformToFloat(Color8* data)
{
    auto width = dibHeader.width;
    auto size = dibHeader.width * dibHeader.height;

    auto ret = (Color*)std::malloc(sizeof(Color) * size);

    for (int i = 0; i < size; i++)
    {
        ret[i].x = static_cast<f32>(data[i].r);
        ret[i].y = static_cast<f32>(data[i].g);
        ret[i].z = static_cast<f32>(data[i].b);

        ret[i] /= 255.f;
    }

    return ret;
}

Image::Color8* Image::transformToChar(Color* data)
{
    auto size = dibHeader.width * dibHeader.height;

    auto ret = (Color8*)std::malloc(sizeof(Color8) * size);

    for (int i = 0; i < size; i++)
    {
        ret[i].r = static_cast<u8>(data[i].x * 255);
        ret[i].g = static_cast<u8>(data[i].y * 255);
        ret[i].b = static_cast<u8>(data[i].z * 255);
    }

    return ret;
}