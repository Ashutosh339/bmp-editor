#include <iostream>
#include <fstream>
#include <cstdint>

// Prevent compiler padding to ensure the struct matches the file format exactly
#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t fileType{0x4D42}; // "BM"
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

    std::cout << "File Type: " << std::hex << fileHeader.fileType << std::endl;
    std::cout << "Width: " << infoHeader.width << " px" << std::endl;
    std::cout << "Height: " << infoHeader.height << " px" << std::endl;
}

int main() {
    // Replace with a path to a real .bmp file
    readBMP("test.bmp");
    return 0;
}