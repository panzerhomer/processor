#pragma once

#include "image.h"
#include "filter.h"

class MosaicFilter : public IFilter {
public:
    MosaicFilter(uint32_t);

    void Apply(Image& image) const;

private:
    uint32_t size_;
};
