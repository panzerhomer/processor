#pragma once

#include <string>
#include <vector>
#include "filter.h"


class ImageProcessor {
public:
    void AddFilter(std::unique_ptr<IFilter>& filter);
    void Process(const std::string& input, const std::string& output);
    
private:
    // std::vector<IFilter*> filters_;
    std::vector<std::unique_ptr<IFilter>> filters_;
};