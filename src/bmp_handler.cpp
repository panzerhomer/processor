#include "bmp_handler.h"
#include <fstream>
#include <stdexcept>

Image BMPReader::Read(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    BMPFileHeader fileHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (!file) {
        throw std::runtime_error("Failed to read BMP file header");
    }
    if (fileHeader.signature != 0x4D42) { 
        throw std::runtime_error("Invalid BMP signature");
    }
        
    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (!file) {
        throw std::runtime_error("Failed to read BMP info header");
    }

    if (infoHeader.bitsPerPixel != 24) {
        throw std::runtime_error("Only 24-bit BMP supported");
    }

    const size_t width = infoHeader.width;
    const size_t height = infoHeader.height;
    const int row_bytes = width * 3;
    const int padding = (4 - (row_bytes % 4)) % 4;

    Image image(width, height);

    for (int row = height - 1; row >= 0; row--) {
        for (size_t col = 0; col < width; col++) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel), 3);
            if (file.fail()) {
                throw std::runtime_error("Error reading pixel data");
            }
            image.setPixel(col, row, pixel);
        }
        
        file.ignore(padding);
        if (!file) {
            throw std::runtime_error("Error skipping row padding");
        }
    }

    return image;
}

void BMPWriter::Write(const std::string& path, const Image& image) {
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to create file: " + path);
    }

    const size_t width = image.width();
    const size_t height = image.height();
    const int row_bytes = width * 3;
    const int padding = (4 - (row_bytes % 4)) % 4;

    BMPFileHeader fileHeader;
    fileHeader.signature = 0x4D42;
    fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + (row_bytes + padding) * height;
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.dataOffset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    BMPInfoHeader infoHeader;
    infoHeader.headerSize = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = 1;
    infoHeader.bitsPerPixel = 24;
    infoHeader.compression = 0;
    infoHeader.imageSize = (row_bytes + padding) * height;
    infoHeader.xPixelsPerMeter = 0;
    infoHeader.yPixelsPerMeter = 0;
    infoHeader.colorsUsed = 0;
    infoHeader.colorsImportant = 0;

    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    for (int row = height - 1; row >= 0; row--) {
        for (size_t col = 0; col < width; col++) {
            Pixel pixel = image.getPixel(col, row);
            file.write(reinterpret_cast<char*>(&pixel), 3);
        }

        for (int p = 0; p < padding; p++) {
            file.put(0);
        }
    }
}