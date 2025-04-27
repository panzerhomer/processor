#include <iostream>
#include <memory>
#include <exception>
#include "command_parser.h"
#include "bmp_io.h"

class ImageProcessor {
    private:
        std::vector<std::unique_ptr<IFilter>> filters_;
    
    public:
        void AddFilter(std::unique_ptr<IFilter> filter) {
            filters_.push_back(std::move(filter));
        }
    
        void Process(const std::string& input, const std::string& output) {
            Image image = BMPReader::Read(input);
    
            for (const auto& filter : filters_) {
                filter->Apply(image);
            }
    
            BMPWriter::Write(output, image);
        }
    };

int main(int argc, char* argv[]) {
    try {
        CommandParser parser;
        parser.Parse(argc, argv);

        ImageProcessor processor;
        for (auto& filter : parser.GetFilters()) {
            processor.AddFilter(std::move(filter));
        }
    
        auto srcFile = parser.GetSourceFile();
        auto destFile = parser.GetDestanationFile();
        processor.Process(srcFile, destFile);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << "unknown" << std::endl;
    }
    return 0;
}