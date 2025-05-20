#include "image.h"
#include "mosaic_filter.h"

MosaicFilter::MosaicFilter(uint32_t size) : size_(size) {}

void MosaicFilter::Apply(Image& image) const {
    const uint32_t size = size_;
    const uint32_t width = image.GetWidth();
    const uint32_t height = image.GetHeight();

    for (uint32_t y = 0; y < height; y += size) {
        for (uint32_t x = 0; x < width; x += size) {
            uint32_t sumRed = 0;
            uint32_t sumGreen = 0;
            uint32_t sumBlue = 0;
            uint32_t count = 0;
            
            for (uint32_t k = 0; k < size; k++) {
                for (uint32_t l = 0; l < size; l++) {
                    uint32_t currentX = x + l;
                    uint32_t currentY = y + k;
                    if (currentX < width && currentY < height) {
                        const Pixel& p = image.GetPixel(currentX, currentY);
                        sumRed += p.red;
                        sumGreen += p.green;
                        sumBlue += p.blue;
                        count += 1;
                    }
                }
            }
            
            uint8_t avgRed   = static_cast<uint8_t>(sumRed / count);
            uint8_t avgGreen = static_cast<uint8_t>(sumGreen / count);
            uint8_t avgBlue  = static_cast<uint8_t>(sumBlue / count);
            
            Pixel avgPixel(avgBlue, avgGreen, avgRed);
            
            for (uint32_t k = 0; k < size; k++) {
                for (uint32_t l = 0; l < size; l++) {
                    uint32_t currentX = x + l;
                    uint32_t currentY = y + k;
                    if (currentX < width && currentY < height) {
                        image.SetPixel(currentX, currentY, avgPixel);
                    }
                }
            }
        }
    }
}