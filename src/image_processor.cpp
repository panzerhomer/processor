#include <iostream>
#include <exception>
#include "bmp_io.h"
#include "image.h"
#include "filter.h"

int main(int argc, char* argv[]) {
    try {
        Image image = BMPReader::Read("../pics/sample.bmp");
        std::cout << "Image dimensions: " 
                  << image.Width() << "x" << image.Height() << std::endl;

        BMPWriter::Write("../flag_tmp.bmp", image); 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}