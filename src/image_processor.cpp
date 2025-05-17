#include <memory>
#include "image_processor.h"
#include "bmp_io.h"
#include "filter.h"

void ImageProcessor::AddFilter(std::unique_ptr<IFilter>& filter) {
    filters_.push_back(std::move(filter));
}
    
void ImageProcessor::Process(const std::string& input, const std::string& output) {
    Image image = BMPReader::Read(input);

    for (const auto& filter : filters_) {
        filter->Apply(image);
    }
    
    BMPWriter::Write(output, image);
}