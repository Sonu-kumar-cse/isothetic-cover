#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

#include "helper_functions/create_empty_bmp.cpp"
#include "helper_functions/find_rectangle.cpp"
#include "helper_functions/outer_cover.cpp"
using namespace std;

// #pragma pack(push, 1) // Ensure no padding in structures
// struct BMPFileHeader {
//     uint16_t fileType;      // File type ("BM")
//     uint32_t fileSize;      // Size of the BMP file in bytes
//     uint16_t reserved1;     // Reserved (0)
//     uint16_t reserved2;     // Reserved (0)
//     uint32_t dataOffset;    // Offset to pixel data
// };

// struct BMPInfoHeader {
//     uint32_t headerSize;    // Size of this header (40 bytes for BITMAPINFOHEADER)
//     int32_t width;          // Image width in pixels
//     int32_t height;         // Image height in pixels
//     uint16_t planes;        // Number of color planes (must be 1)
//     uint16_t bitsPerPixel;  // Bits per pixel (e.g., 24 for RGB)
//     uint32_t compression;   // Compression type (0 for no compression)
//     uint32_t imageSize;     // Size of pixel data (may be 0 if uncompressed)
//     int32_t xResolution;    // Horizontal resolution (pixels per meter)
//     int32_t yResolution;    // Vertical resolution (pixels per meter)
//     uint32_t colorsUsed;    // Number of colors in the palette
//     uint32_t importantColors; // Number of important colors
// };
// #pragma pack(pop)



bool createWhiteBMP(const std::string& sourcePath, const std::string& destPath) {
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    if (!sourceFile) {
        std::cerr << "Error: Unable to open source file!" << std::endl;
        return false;
    }

    // Read BMP and DIB headers
    BMPFileHeader bmpHeader;
    BMPInfoHeader dibHeader;

    sourceFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPFileHeader));
    sourceFile.read(reinterpret_cast<char*>(&dibHeader), sizeof(BMPInfoHeader));

    if (bmpHeader.fileType != 0x4D42) { // 'BM' in little-endian
        std::cerr << "Error: Not a valid BMP file!" << std::endl;
        return false;
    }

    // Ensure 24-bit BMP (no alpha)
    if (dibHeader.bitsPerPixel != 24 || dibHeader.compression != 0) {
        std::cerr << "Error: Only uncompressed 24-bit BMP files are supported!" << std::endl;
        return false;
    }

    int32_t width = dibHeader.width;
    int32_t height = dibHeader.height;

    // Calculate row size (padded to a multiple of 4 bytes)
    int rowSize = (width * 4) ;
    int imageSize = rowSize * height;

    // Update DIB header for the new image
    dibHeader.imageSize = imageSize;
    bmpHeader.fileSize = bmpHeader.dataOffset + imageSize;

    // Create a white pixel buffer
    std::vector<uint8_t> whiteRow(rowSize, 255); // Each row filled with white pixels (RGB: 255,255,255)

    std::ofstream destFile(destPath, std::ios::binary);
    if (!destFile) {
        std::cerr << "Error: Unable to create destination file!" << std::endl;
        return false;
    }

    // Write the headers to the destination file
    dibHeader.bitsPerPixel=24;
    destFile.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPFileHeader));
    destFile.write(reinterpret_cast<const char*>(&dibHeader), sizeof(BMPInfoHeader));

    // Write white pixels to fill the image
    for (int i = 0; i < height; ++i) {
        for(int j=0;j<rowSize;j++)
        {
            uint8_t x=255;
            destFile.write(reinterpret_cast<char*>(&x), 1);
        }
    }

    std::cout << "White BMP created successfully!" << std::endl;
    return true;
}

void readBMP(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        cerr << "Error: Could not open file!" << endl;
        return;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    // Read the headers
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Validate BMP file type
    if (fileHeader.fileType != 0x4D42) { // "BM" in little-endian
        cerr << "Error: Not a valid BMP file!" << endl;
        return;
    }

    // Print header information
    cout << "Width: " << infoHeader.width << " pixels" << endl;
    cout << "Height: " << infoHeader.height << " pixels" << endl;
    cout << "Bits per Pixel: " << infoHeader.bitsPerPixel << endl;
    cout << "Image Size: " << infoHeader.imageSize << " bytes" << endl;
    cout << "planes : " << infoHeader.planes << " bytes" << endl;
    cout << "compression : " << infoHeader.compression << " bytes" << endl;
    cout << "x resolution : " << infoHeader.xResolution << " bytes" << endl;
    cout << "y resolution : " << infoHeader.yResolution << " bytes" << endl;

    // Read pixel data
    file.seekg(fileHeader.dataOffset, ios::beg);
    vector<uint8_t> pixelData(infoHeader.imageSize);
    file.read(reinterpret_cast<char*>(pixelData.data()), infoHeader.imageSize);

    // Process pixel data (e.g., display the RGB values of the first pixel)
    if (infoHeader.bitsPerPixel == 24) { // 24-bit BMP (RGB)
        cout << "First pixel RGB values: "
                  << "R=" << (int)pixelData[2] << " "
                  << "G=" << (int)pixelData[1] << " "
                  << "B=" << (int)pixelData[0] << endl;
    }

    file.close();
}


int main() {

    string filePath="inputs/many_obj.bmp";
    // cout<<"enter input path:";
    // cin>>filePath;
    if(!createEmptyBMP(filePath,"outputs/output.bmp"))
    {
        cout<<"someting wrong";
        return 1;
    }

    std::fstream white_bmp("outputs/output.bmp", std::ios::in | std::ios::out | std::ios::binary);
    if (!white_bmp) {
        std::cerr << "Error: Unable to open file for reading and writing!" << std::endl;
        return 1;
    }

    ifstream input_bmp(filePath, ios::binary);
    if (!input_bmp) {
        cerr << "Error: Could not open file!" << endl;
        return 1;
    }
    BMPFileHeader fileHeader_input;
    BMPInfoHeader infoHeader_input;

    // Read the headers
    input_bmp.read(reinterpret_cast<char*>(&fileHeader_input), sizeof(fileHeader_input));
    input_bmp.read(reinterpret_cast<char*>(&infoHeader_input), sizeof(infoHeader_input));

    // Validate BMP file type
    if (fileHeader_input.fileType != 0x4D42) { // "BM" in little-endian
        cerr << "Error: Not a valid BMP file!" << endl;
        return 1;
    }

    int grid_size;
    cout<<"enter grid size:";
    
    cin>>grid_size;
    
    int height=(int)infoHeader_input.height;
    int width=(int)infoHeader_input.width;

    height*=-1;

    int offset=(int)fileHeader_input.dataOffset;

    int rowsize=(width*3+3) & ~3;
    cout<<height<<" "<<width<<endl;
    vector<int> rectangle=get_rectangle(white_bmp,input_bmp,offset,rowsize,height,width,grid_size);

    for(int i=0;i<rectangle.size();i++)
    {
        cout<<rectangle[i]<<" ";
    }
    cout<<endl;

    cout<<offset<<endl;

    cout<<rowsize<<endl;
    create_outer_cover(input_bmp,white_bmp,offset,rectangle,rowsize,height,width,grid_size);

    input_bmp.close();
    white_bmp.close();



    return 0;
}

