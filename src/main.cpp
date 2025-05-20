#include <iostream>
#include <memory>
#include <exception>
#include "command_parser.h"
#include "image_processor.h"

int main(int argc, char* argv[]) {
    try {
        CommandParser parser;
        parser.Parse(argc, argv);

        ImageProcessor processor;
        for (auto& filter : parser.GetFilters()) {
            processor.AddFilter(filter);
        }
    
        std::string srcFile = parser.GetSourceFile();
        std::string destFile = parser.GetDestanationFile();
        processor.Process(srcFile, destFile);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << "unknown error" <<  e.what() << std::endl;
        return 1;
    }
    return 0;
}