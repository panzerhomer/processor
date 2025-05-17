#pragma once

#include "image.h"
#include "filter.h"

class GreyFilter : public IFilter {
public:
    void Apply(Image&) const;
};
