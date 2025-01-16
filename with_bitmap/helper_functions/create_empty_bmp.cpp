#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include<vector>

using namespace std;


#pragma pack(push, 1) // Ensure no padding in structures
struct BMPFileHeader {
    uint16_t fileType;      // File type ("BM")
    uint32_t fileSize;      // Size of the BMP file in bytes
    uint16_t reserved1;     // Reserved (0)
    uint16_t reserved2;     // Reserved (0)
    uint32_t dataOffset;    // Offset to pixel data
};

struct BMPInfoHeader {
    uint32_t headerSize;    // Size of this header (40 bytes for BITMAPINFOHEADER)
    int32_t width;          // Image width in pixels
    int32_t height;         // Image height in pixels
    uint16_t planes;        // Number of color planes (must be 1)
    uint16_t bitsPerPixel;  // Bits per pixel (e.g., 24 for RGB)
    uint32_t compression;   // Compression type (0 for no compression)
    uint32_t imageSize;     // Size of pixel data (may be 0 if uncompressed)
    int32_t xResolution;    // Horizontal resolution (pixels per meter)
    int32_t yResolution;    // Vertical resolution (pixels per meter)
    uint32_t colorsUsed;    // Number of colors in the palette
    uint32_t importantColors; // Number of important colors
};
#pragma pack(pop)



bool createEmptyBMP(const string &sourcepath,const string& filePath) {
    
    ifstream file1(sourcepath, ios::binary);
    if (!file1) {
        cerr << "Error: Could not open file!" << endl;
        return false;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    // Read the headers
    file1.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file1.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    
    ofstream file(filePath, ios::binary);
    if (!file) {
        cerr << "Error: Could not create file!" << endl;
        return false;
    }

    

    // Write headers
    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    int wid=infoHeader.width;
    int total_row=(wid*3 + 3)& ~3;
    int hei=infoHeader.height;
    cout<<"height="<<hei<<" width="<<wid<<endl;
    if(hei<0)hei*=-1;
    // Write pixel data (solid color: blue)
    for (int i = 0; i < hei; ++i) {
        if(i==0)cout<<"hello";
        for (int j = 0; j < total_row; ++j) {
            uint8_t blue = 255, green = 0, red = 0; // Blue color
            file.write(reinterpret_cast<char*>(&blue), 1);
            // file.write(reinterpret_cast<char*>(&alpha), 1);
        }
    }

    file.close();
    cout << "BMP file created successfully!" << endl;
    return true;
}
