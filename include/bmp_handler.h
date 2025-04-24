#pragma once

#include <cstdint>
#include <string>
#include "image.h"

namespace BMPConstants {
    constexpr auto ERROR_OPEN_FILE = "Failed to open file: ";
    constexpr auto ERROR_READ_HEADER = "Failed to read BMP header";
    constexpr auto ERROR_INVALID_SIGNATURE = "Invalid BMP signature";
    constexpr auto ERROR_UNSUPPORTED_BPP = "Only 24-bit BMP supported";
    constexpr auto ERROR_READ_PIXELS = "Error reading pixel data";
    constexpr auto ERROR_SKIP_PADDING = "Error skipping row padding";
    constexpr auto ERROR_CREATE_FILE = "Failed to create file: ";

    constexpr uint16_t SIGNATURE_BM = 0x4D42;  // 'BM'
    constexpr int BITS_PER_PIXEL_24 = 24;
    constexpr int BYTES_PER_PIXEL = 3;
    constexpr int PADDING_ALIGNMENT = 4;
    constexpr uint8_t PADDING_VALUE = 0;
    
    constexpr uint16_t DEFAULT_PLANES = 1;
    constexpr uint32_t COMPRESSION_NONE = 0;
    constexpr uint32_t DEFAULT_RESOLUTION = 0;
    constexpr uint32_t NO_COLOR_TABLE = 0;
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
