#pragma once

#include <cstdint>
#include <vector>

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
};

class Image {
public:
    Image(uint32_t width, uint32_t height);

    Pixel& getPixel(uint32_t x, uint32_t y);
    const Pixel& getPixel(uint32_t x, uint32_t y) const;
    void setPixel(uint32_t x, uint32_t y, const Pixel& pixel);

    uint32_t width() const;
    uint32_t height() const;

private:
    uint32_t width_;
    uint32_t height_;
    std::vector<Pixel> pixels_;
};
