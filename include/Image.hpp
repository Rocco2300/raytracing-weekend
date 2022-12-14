#pragma once

#include "Vec3.hpp"
#include "Types.hpp"

#include <string>

#include "Vec3.hpp"

class Image
{
private:
#pragma pack(push, 1)
    struct Color8
    {
        u8 b, g, r;
    };

    struct ImageHeader
    {
        u16 header;
        u32 size;
        u16 reserved1;
        u16 reserved2;
        u32 startingOffset;
    };

    struct DIBHeader
    {
        u32 headerSize;
        u32 width;
        u32 height;
        u16 colorPlanes;
        u16 bitsPerPixel;
        u32 compression;
        u32 imageSize;
        u32 horizontalResolution;
        u32 verticalResolution;
        u32 colorNumber;
        u32 importantColors;
    };
#pragma pack(pop)

private:
    ImageHeader header;
    DIBHeader dibHeader;
    Color* pixels;

public:
    Image() : header{}, dibHeader{}, pixels{nullptr} { }
    Image(int width, int height);

    ~Image();

    Color& operator[](int index);
    Color& operator()(int x, int y);
    Color& operator[](int index) const;
    Color& operator()(int x, int y) const;

    u32 getWidth() const;
    u32 getHeight() const;

    void save(const std::string& path);

    bool load(const std::string& path);
    bool create(int width, int height);

private:
    u8 getPadding() const;

    Color* transformToFloat(Color8* data);
    Color8* transformToChar(Color* data);
};
