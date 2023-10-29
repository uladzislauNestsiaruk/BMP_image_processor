//
// Created by vlad on 25.10.23.
//

#ifndef CPP_HSE_BMP_STREAM_H
#define CPP_HSE_BMP_STREAM_H

#include <fstream>

#include "bmp.h"

static const uint16_t BMP_SIGNATURE = 0x4d42;
static const uint16_t BMP_BIT_PER_PIXEL = 24;
static const uint32_t DWORD = 32;

class BMPStream {

public:
    explicit BMPStream(BMP& image) : image_(image){};

    const std::string& GetFilename() const {
        return filename_;
    }

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
    BMP& image_;
};

#endif  // CPP_HSE_BMP_STREAM_H
