#include <gtest/gtest.h>
#include "image.h"

TEST(ImageTest, CreateImage) {
    uint32_t height = 2;
    uint32_t width = 2;
    
    Image img(width, height);
    
    EXPECT_EQ(img.GetWidth(), width);
    EXPECT_EQ(img.GetHeight(), height);
}

TEST(ImageTest, SetAndGetPixelFirst) {
    uint32_t height = 2;
    uint32_t width = 2;
    
    Image img(width, height);
    Pixel redPixel(0, 0, 255); 

    img.SetPixel(0, 0, redPixel);
    Pixel retrievedPixel = img.GetPixel(0, 0);

    EXPECT_EQ(retrievedPixel.red, redPixel.red);
    EXPECT_EQ(retrievedPixel.green, redPixel.green);
    EXPECT_EQ(retrievedPixel.blue, redPixel.blue);
}

TEST(ImageTest, SetAndGetPixelLast) {
    uint32_t height = 2;
    uint32_t width = 2;
    
    Image img(width, height);
    Pixel redPixel(255, 255, 0); 

    img.SetPixel(1, 1, redPixel);
    Pixel retrievedPixel = img.GetPixel(1, 1);

    EXPECT_EQ(retrievedPixel.red, redPixel.red);
    EXPECT_EQ(retrievedPixel.green, redPixel.green);
    EXPECT_EQ(retrievedPixel.blue, redPixel.blue);
}

TEST(ImageTest, SetPixelOutOfBounds) {
    uint32_t height = 2;
    uint32_t width = 2;
    
    Image img(width, height);
    Pixel redPixel(0, 0, 255); 

    EXPECT_THROW(img.SetPixel(2, 2, redPixel), std::out_of_range);
}

TEST(ImageTest, GetPixelOutOfBounds) {
    uint32_t height = 2;
    uint32_t width = 2;
    
    Image img(width, height);

    EXPECT_THROW(img.GetPixel(2, 2), std::out_of_range);
}
