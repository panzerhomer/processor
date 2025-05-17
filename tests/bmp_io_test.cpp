#include <gtest/gtest.h>
#include <filesystem>
#include "bmp_io.h"

TEST(BMPReaderTest, ReadFlagImage) {
    std::string input = "pics/flag.bmp";
    Image image = BMPReader::Read(input);
    EXPECT_EQ(image.GetWidth(), 16); 
    EXPECT_EQ(image.GetHeight(), 16); 
}

TEST(BMPReaderTest, ReadNatureImage) {
    std::string input = "pics/nature.bmp";
    Image image = BMPReader::Read(input);
    EXPECT_EQ(image.GetWidth(), 640); 
    EXPECT_EQ(image.GetHeight(), 426); 
}

TEST(BMPReaderTest, ReadSquareImage) {
    std::string input = "pics/square.bmp";
    Image image = BMPReader::Read(input);
    EXPECT_EQ(image.GetWidth(), 2); 
    EXPECT_EQ(image.GetHeight(), 2); 
}

TEST(BMPReaderTest, FailReadNonBMPFile) {
    std::string input = "pics/test.png";
    EXPECT_THROW({
        Image image = BMPReader::Read(input);
    }, std::exception);
}

TEST(BMPReaderWriterTest, WriteAndReadBack) {
    std::string input = "pics/flag.bmp";
    Image originalImage = BMPReader::Read(input);
    
    std::string tempOutput = "temp_flag.bmp";
    
    ASSERT_NO_THROW(BMPWriter::Write(tempOutput, originalImage));
    
    Image loadedImage = BMPReader::Read(tempOutput);
    
    EXPECT_EQ(loadedImage.GetWidth(), originalImage.GetWidth());
    EXPECT_EQ(loadedImage.GetHeight(), originalImage.GetHeight());
    
    for (size_t y = 0; y < originalImage.GetHeight(); y++) {
        for (size_t x = 0; x < originalImage.GetWidth(); x++) {
            Pixel loadedPixel = loadedImage.GetPixel(x, y);
            Pixel originalPixel = originalImage.GetPixel(x, y);
    
            EXPECT_TRUE(loadedPixel.red == originalPixel.red &&
                        loadedPixel.green == originalPixel.green &&
                        loadedPixel.blue == originalPixel.blue)
                << "Mismatch at position (" << x << ", " << y << ")";
        }
    }

    std::filesystem::remove(tempOutput);
}

