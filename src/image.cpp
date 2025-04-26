#include <stdexcept>
#include "image.h"

Image::Image(uint32_t width = 0, uint32_t height = 0) {
    width_ = width;
    height_ = height;
    pixels_.resize(width * height);
}

Pixel& Image::GetPixel(uint32_t x, uint32_t y) {
    ValidateHeightAndWeight(x, y);
    uint32_t position = y * width_ + x;
    return pixels_.at(position);
}

const Pixel& Image::GetPixel(uint32_t x, uint32_t y) const {
    ValidateHeightAndWeight(x, y);
    uint32_t position = y * width_ + x;
    return pixels_.at(position);
}

void Image::SetPixel(uint32_t x, uint32_t y, const Pixel& pixel) {
    ValidateHeightAndWeight(x, y);
    uint32_t position = y * width_ + x;
    pixels_[y * width_ + x] = pixel;
}

void Image::ValidateHeightAndWeight(uint32_t x, uint32_t y) const {
    if (x > width_ || y > height_) {
        throw std::out_of_range(ImageConstants::COORDS_OUT_OF_RANGE);
    }
}

uint32_t Image::GetWidth() const { 
    return width_; 
}

uint32_t Image::GetHeight() const { 
    return height_; 
}