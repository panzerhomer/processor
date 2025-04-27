#include <cstddef>
#include <iostream>
#include "image.h"
#include "crop_filter.h"

CropFilter::CropFilter(uint32_t width, uint32_t height) : width_(width), height_(height) {
    std::cout << width << " " << height << "\n";
}
    
void CropFilter::Apply(Image& image) const {
    uint32_t imageWidth = image.GetWidth();
    uint32_t imageHeight = image.GetHeight();

    const bool isGreaterOriginalImage = (imageHeight <= height_ && imageWidth <= width_);
    const bool isZero = (height_ * width_ == 0);
    if (isGreaterOriginalImage || isZero) {
        throw std::invalid_argument("Crop width and height cannot be less than 0 or exceed the original size");
    }

    uint32_t offsetX = (imageWidth > width_) ? (imageWidth - width_) / 2 : 0;
    uint32_t offsetY = (imageHeight > height_) ? (imageHeight - height_) / 2 : 0;

    Image newImage(width_, height_);

    for (size_t y = 0; y < height_; y++) {
        for (size_t x = 0; x < width_; x++) {
            newImage.SetPixel(x, y, image.GetPixel(x + offsetX, y + offsetY));
        }
    }

    image = newImage;
}
