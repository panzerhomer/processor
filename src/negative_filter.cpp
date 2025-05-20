#include "image.h"
#include "negative_filter.h"

void NegativeFilter::Apply(Image& image) const {
    uint32_t width = image.GetWidth();
    uint32_t height = image.GetHeight();
    
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            Pixel pixel = image.GetPixel(x, y);

            pixel.blue = 255 - pixel.blue;
            pixel.green = 255 - pixel.green;
            pixel.red = 255 - pixel.red;
            
            image.SetPixel(x, y, pixel);
        }
    }
}