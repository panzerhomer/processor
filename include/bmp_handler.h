#pragma once

#include <string>
#include "image.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cstdint>

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
