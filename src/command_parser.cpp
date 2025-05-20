#include <iostream>
#include <stdexcept>
#include "command_parser.h"
#include "filter.h"
#include "crop_filter.h"
#include "grey_filter.h"
#include "mosaic_filter.h"

void CommandParser::Parse(int argc, char* argv[]) {
    if (argc < 3) {
        if (argc == 2) {
            std::string currentArgv(argv[1]);
            if (currentArgv == "-h" || currentArgv == "--help") {
                PrintHelp();
                exit(0);
            }
        }
        throw std::invalid_argument("Check your arguments");
    }

    srcFile_ = argv[1];
    destFile_ = argv[2];

    for (int i = 3; i < argc; i++) {
        std::string currentArgv(argv[i]);
        if (currentArgv == "-crop") {
            if (i + 2 >= argc) {
                throw std::invalid_argument("Must be two arguments for -crop");
            }
            uint32_t width;
            uint32_t height;
            try {
                width = std::stoul(argv[i + 1]);
                height = std::stoul(argv[i + 2]);

                if (width <= 0 || height <= 0) {
                    throw std::invalid_argument("Crop dimensions must be positive");
                }

                i += 2;
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid -crop arguments");
            }
            filters_.push_back(std::make_unique<CropFilter>(width, height));
        } else if (currentArgv == "-gs") {
            filters_.push_back(std::make_unique<GreyFilter>());
        } else if (currentArgv == "-ms") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("Must be one argument for -ms");
            }
            uint32_t pixelSize;
            try {
                pixelSize = std::stoul(argv[i + 1]);
                if (pixelSize <= 0) {
                    throw std::invalid_argument("Pixel size must be positive");
                }

                filters_.push_back(std::make_unique<MosaicFilter>(pixelSize));
                i++; 
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid -ms argument");
            }
        } else {
            PrintHelp();
            throw std::invalid_argument("Unknown argument: " + currentArgv);
        }
    }
}

void CommandParser::PrintHelp() {
    std::cout << "Usage: ./image_processor ./input.bmp ./output.bmp [FILTERS...]\n"
        << "Exmaple: ./image_processor ./input.bmp ./output.bmp -gs -ms -crop 200 200\n"
        << "Upload 24 bit bmp files only!\n"
        << "First argument is source file\n"
        << "Second argument is destination file\n\n"
        << "Filters:\n"
        << "  -crop [width] [height]  Crop image to the given width and height\n"
        << "  -gs                             Apply grey filter\n"
        << "  -ms,                          Apply mosaic filter\n"
        << "  -h, --help                 Show this help message\n";
};
    
std::string CommandParser::GetSourceFile() {
    return srcFile_;
}

std::string CommandParser::GetDestanationFile() {
    return destFile_;
}

std::vector<std::unique_ptr<IFilter>>& CommandParser::GetFilters() {
    return filters_;
}
