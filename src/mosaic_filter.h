#pragma once

#include "image.h"
#include "filter.h"

class MosaicFilter : public IFilter {
public:
    void Apply(Image& image) const;
};
