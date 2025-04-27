#include <fstream>
#include <stdexcept>
#include <iostream>
#include "bmp_io.h"

using namespace BMPConstants;

Image BMPReader::Read(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (file.fail()) {
        throw std::runtime_error(ERROR_OPEN_FILE + path);
    }

    BMPFileHeader fileHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (file.fail()) {
        throw std::invalid_argument(ERROR_READ_HEADER);
    }
    if (fileHeader.signature != SIGNATURE_BM) {
        throw std::invalid_argument(ERROR_INVALID_SIGNATURE);
    }

    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (file.fail()) {
        throw std::runtime_error(ERROR_READ_HEADER);
    }

    if (infoHeader.bitsPerPixel != BITS_PER_PIXEL_24) {
        throw std::invalid_argument(ERROR_UNSUPPORTED_BPP);
    }

    const size_t width = infoHeader.width;
    const size_t height = infoHeader.height;
    const int rowBytes = width * BYTES_PER_PIXEL; 
    const int padding = (PADDING_ALIGNMENT - (rowBytes % PADDING_ALIGNMENT)) % PADDING_ALIGNMENT; 

    Image image(width, height);

    for (int row = height - 1; row >= 0; row--) {
        for (size_t col = 0; col < width; col++) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel), BYTES_PER_PIXEL);
            if (file.fail()) {
                throw std::runtime_error(ERROR_READ_PIXELS);
            }
            image.SetPixel(col, row, pixel);
        }
        
        for (int i = 0; i < padding; i++) {
            char temp;
            file.get(temp);
        }
    }

    return image;
}

void BMPWriter::Write(const std::string& path, const Image& image) {
    std::ofstream file(path, std::ios::binary);
    if (file.fail()) {
        throw std::runtime_error(ERROR_CREATE_FILE + path);
    }

    const size_t width = image.GetWidth();
    const size_t height = image.GetHeight();
    const int rowBytes = width * BYTES_PER_PIXEL;
    const int padding = (PADDING_ALIGNMENT - (rowBytes % PADDING_ALIGNMENT)) % PADDING_ALIGNMENT;

    BMPFileHeader fileHeader;
    fileHeader.signature = SIGNATURE_BM;
    fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + (rowBytes + padding) * height;
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.dataOffset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    BMPInfoHeader infoHeader;
    infoHeader.headerSize = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = DEFAULT_PLANES;
    infoHeader.bitsPerPixel = BITS_PER_PIXEL_24;
    infoHeader.compression = COMPRESSION_NONE;
    infoHeader.imageSize = (rowBytes + padding) * height;
    infoHeader.xPixelsPerMeter = DEFAULT_RESOLUTION;
    infoHeader.yPixelsPerMeter = DEFAULT_RESOLUTION;
    infoHeader.colorsUsed = NO_COLOR_TABLE;
    infoHeader.colorsImportant = NO_COLOR_TABLE;

    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (file.fail()) {
        throw std::runtime_error(ERROR_CREATE_FILE);
    }

    for (int row = height - 1; row >= 0; row--) {
        for (size_t col = 0; col < width; col++) {
            const Pixel pixel = image.GetPixel(col, row);
            file.write(reinterpret_cast<const char*>(&pixel), BYTES_PER_PIXEL);
            if (file.fail()) {
                throw std::runtime_error(ERROR_CREATE_FILE);
            }
        }

        for (int p = 0; p < padding; p++) {
            file.put(0);
        }
    }
}