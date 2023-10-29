//
// Created by vlad on 25.10.23.
//

#ifndef CPP_HSE_BMP_STREAM_H
#define CPP_HSE_BMP_STREAM_H

#include <fstream>

#include "color_matrix.h"

static const uint16_t BMP_SIGNATURE= 0x4d42;
static const uint16_t BMP_BIT_PER_PIXEL = 24;
static const uint16_t BMP_FILE_HEADER_SIZE = 14;
static const uint32_t DWORD = 32;


struct BMPFileHeader{
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
}__attribute__((packed));

struct BMPDibHeader{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t color_planes;
    uint16_t bit_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t h_resolution;
    uint32_t v_resolution;
    uint32_t number_of_colors;
    uint32_t important_colors;
}__attribute__((packed));

class BMPStream {

public:
    BMPStream(){};

    const std::string& GetFilename() const {return filename_;}

    const BMPFileHeader& GetFileHeader() const {return file_header_;}

    const BMPDibHeader& GetDibHeader() const {return dib_header_;}

    ColorMatrix& GetPixelArray() {return pixel_array_;}

    void SetPixelArray(ColorMatrix& pixel_array){pixel_array_ = pixel_array;}

    void UpdatePixelArraySizeDescription(uint32_t new_image_size);

    void SetWidth(int32_t width){dib_header_.width = width;}

    void SetHeight(int32_t height){dib_header_.height = height;}

    void OpenInputStream(const std::string& filename);

    void CloseInputStream();

    void ReadBMP();

    void OpenOutputStream(const std::string& output_filename);

    void CloseOutputStream();

    void PrintBMPImage();

private:

    void ReadBMPFileHeader();

    void ReadBMPDibHeader();

    void ReadPixelArray();

    void PrintBMPFileHeader();

    void PrintBMPDibHeader();

    void PrintBMPPixelArray();

    std::fstream file_;
    std::ofstream output_file_;
    std::string filename_;
    std::string output_filename_;
    BMPFileHeader file_header_;
    BMPDibHeader dib_header_;
    ColorMatrix pixel_array_;
};

#endif  // CPP_HSE_BMP_STREAM_H
