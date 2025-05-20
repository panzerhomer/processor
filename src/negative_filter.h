#pragma once

#include "image.h"
#include "filter.h"

class NegativeFilter : public IFilter {
public:
    void Apply(Image&) const;
};
