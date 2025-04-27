#include <iostream>
#include <stdexcept>
#include "command_parser.h"
#include "filter.h"
#include "crop_filter.h"
#include "grey_filter.h"

void CommandParser::Parse(int argc, char* argv[]) {
    if (argc < 3) {
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
            int width;
            int height;
            try {
                width = atoi(argv[i + 1]);
                height = atoi(argv[i + 2]);
                i += 2;
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid -crop arguments");
            }
            filters_.push_back(std::make_unique<CropFilter>(width, height));
        } else if (currentArgv == "-gs") {
            filters_.push_back(std::make_unique<GreyFilter>());
        } else if (currentArgv == "-h" || currentArgv == "--help") {
            PrintHelp();
            exit(0);
        } else {
            throw std::invalid_argument("Unknown argument: " + currentArgv);
        }
    }
}

void CommandParser::PrintHelp() {
    std::cout << "Usage: ./image_processor ./input.bmp ./output.bmp [FILTERS...]\n"
        << "Upload 24 bit bmp files only!\n"
        << "First argument is source file\n"
        << "Second argument is destination file\n\n"
        << "Filters:\n"
        << "  -crop    Crop image to the given width and height\n"
        << "  -gs                       Apply grey scale filter\n"
        << "  -h, --help                 Show this help message\n";
}
    
std::string CommandParser::GetSourceFile() {
    return srcFile_;
}

std::string CommandParser::GetDestanationFile() {
    return destFile_;
}

std::vector<std::unique_ptr<IFilter>> CommandParser::GetFilters() {
    return std::move(filters_);
}
