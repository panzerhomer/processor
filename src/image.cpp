#include "image.h"
#include <stdexcept>

Image::Image(uint32_t width = 0, uint32_t height = 0) {
    width_ = width;
    height_ = height;
    pixels_.resize(width * height);
}

Pixel& Image::getPixel(uint32_t x, uint32_t y) {
    return pixels_.at(y * width_ + x);
}

const Pixel& Image::getPixel(uint32_t x, uint32_t y) const {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Coordinates are outside of width or/and height");
    }

    uint32_t position = y * width_ + x;
    return pixels_.at(position);
}

void Image::setPixel(uint32_t x, uint32_t y, const Pixel& pixel) {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Coordinates are outside of width or/and height");
    }

    uint32_t position = y * width_ + x;
    if (position >= pixels_.size()) {
        throw std::logic_error("Computed position exceeds pixel buffer size");
    }
    pixels_[y * width_ + x] = pixel;
}

uint32_t Image::width() const { 
    return width_; 
}

uint32_t Image::height() const { 
    return height_; 
}