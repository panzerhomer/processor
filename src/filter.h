#pragma once
#include "image.h"

class IFilter {
public:
    virtual ~IFilter() = default;
    virtual void Apply(Image& image) const = 0;
};


            