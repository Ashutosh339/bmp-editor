#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#pragma pack(push, 1)
struct RGBPixel {
    uint8_t r, g, b;
};

// Validate that RGBPixel is exactly 3 bytes
static_assert(sizeof(RGBPixel) == 3, "RGBPixel must be exactly 3 bytes");

struct BMPFileHeader {
    uint16_t fileType{0x4D42};
    uint32_t fileSize{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offsetData{0};
};

struct BMPInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bitCount{0};
    uint32_t compression{0};
    uint32_t sizeImage{0};
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};
    uint32_t colorsImportant{0};
};
#pragma pack(pop)

void readBMP(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file." << std::endl;
        return;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Move file pointer to the start of pixel data
    file.seekg(fileHeader.offsetData, std::ios::beg);

    // Calculate padding per row (each row must be a multiple of 4 bytes)
    int row_bytes = infoHeader.width * sizeof(RGBPixel);
    uint8_t padding = (4 - (row_bytes % 4)) % 4;

    // Use std::vector for safe memory management
    std::vector<RGBPixel> rawimage(infoHeader.width * infoHeader.height);

    for (int i = 0; i < infoHeader.height; ++i) {
        // Read the entire row
        file.read(reinterpret_cast<char*>(&rawimage[i * infoHeader.width]), row_bytes);
        
        // Skip the padding bytes
        file.seekg(padding, std::ios::cur);
    }

    std::cout << "Successfully read " << rawimage.size() << " pixels." << std::endl;
}
int main() {
    // Your logic here
    readBMP("test.bmp");
    return 0;
}