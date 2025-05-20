#pragma once

#include <cstdint>
#include <vector>

namespace ImageConstants {
    const auto COORDS_OUT_OF_RANGE = "Coordinates are outside of width or/and height";
}

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;

    Pixel(uint8_t b, uint8_t g , uint8_t r) {
        blue = b;
        green = g;
        red = r;
    }

    Pixel() {}
};

class Image {
public:
    Image(uint32_t width, uint32_t height);

    Pixel& GetPixel(uint32_t x, uint32_t y);
    const Pixel& GetPixel(uint32_t x, uint32_t y) const;
    void SetPixel(uint32_t x, uint32_t y, const Pixel& pixel);

    void ValidateHeightAndWeight(uint32_t x, uint32_t y) const;

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    
private:
    uint32_t width_;
    uint32_t height_;
    std::vector<Pixel> pixels_;
};
