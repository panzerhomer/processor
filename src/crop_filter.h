#pragma once

#include "image.h"
#include "filter.h"

class CropFilter : public IFilter {
public:
    CropFilter(uint32_t, uint32_t);
    
    void Apply(Image&) const;
    
private:
    uint32_t width_;
    uint32_t height_;
};

