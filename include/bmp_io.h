#pragma once

#include <cstdint>
#include <string>
#include "image.h"

namespace BMPConstants {
    const auto ERROR_OPEN_FILE = "Failed to open file: ";
    const auto ERROR_READ_HEADER = "Failed to read BMP header";
    const auto ERROR_INVALID_SIGNATURE = "Wrong BMP signature";
    const auto ERROR_UNSUPPORTED_BPP = "Only 24-bit BMP supported";
    const auto ERROR_READ_PIXELS = "Error reading pixel data";
    const auto ERROR_SKIP_PADDING = "Error skipping row padding";
    const auto ERROR_CREATE_FILE = "Failed to create file: ";

    const uint16_t SIGNATURE_BM = 0x4D42;  // 'BM'
    const int BITS_PER_PIXEL_24 = 24;
    const int BYTES_PER_PIXEL = 3;
    const int PADDING_ALIGNMENT = 4;
    
    const uint16_t DEFAULT_PLANES = 1;
    const uint32_t COMPRESSION_NONE = 0;
    const uint32_t DEFAULT_RESOLUTION = 0;
    const uint32_t NO_COLOR_TABLE = 0;
}

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t signature;        
    uint32_t fileSize;        
    uint16_t reserved1;         
    uint16_t reserved2;         
    uint32_t dataOffset;       
};

struct BMPInfoHeader {
    uint32_t headerSize;       
    int32_t width;              
    int32_t height;             
    uint16_t planes;            
    uint16_t bitsPerPixel;    
    uint32_t compression;       
    uint32_t imageSize;        
    int32_t xPixelsPerMeter; 
    int32_t yPixelsPerMeter; 
    uint32_t colorsUsed;       
    uint32_t colorsImportant;  
};
#pragma pack(pop)

class BMPReader {
public:
    static Image Read(const std::string& path);
};
    
class BMPWriter {
public:
    static void Write(const std::string& path, const Image& image);
};
