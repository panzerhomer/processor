#include <iostream>
#include <exception>
#include "bmp_handler.h"
#include "image.h"

int main(int argc, char* argv[]) {
    try {
        Image image = BMPReader::Read("../flag.bmp");
        std::cout << "Image dimensions: " 
                  << image.width() << "x" << image.height() << std::endl;

        BMPWriter::Write("../flag_tmp.bmp", image); 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}