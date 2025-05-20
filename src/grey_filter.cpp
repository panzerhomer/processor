#include "image.h"
#include "grey_filter.h"

void GreyFilter::Apply(Image& image) const {
    uint32_t width = image.GetWidth();
    uint32_t height = image.GetHeight();
    
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            Pixel origPixel = image.GetPixel(x, y);
            
            uint8_t grey = static_cast<uint8_t>(0.299 * origPixel.red + 0.587 * origPixel.green + 0.114 * origPixel.blue);
            
            Pixel greyPixel = origPixel;
            greyPixel.red   = grey;
            greyPixel.green = grey;
            greyPixel.blue  = grey;
                
            image.SetPixel(x, y, greyPixel);
        }
    }
}