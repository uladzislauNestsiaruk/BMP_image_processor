//
// Created by vlad on 29.10.23.
//

#ifndef CPP_HSE_BMP_H
#define CPP_HSE_BMP_H

#include <cstdint>

#include "color_matrix.h"

static const uint16_t BMP_FILE_HEADER_SIZE = 14;
/// Structure to describe BMP file header
struct BMPFileHeader {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} __attribute__((packed));
/// Structure to describe BMP dib header
struct BMPDibHeader {
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
} __attribute__((packed));

class BMP {

public:
    BMP(){};
    /// BMP file header getter
    BMPFileHeader& GetFileHeader() {
        return file_header_;
    }
    /// BMP dib header getter
    BMPDibHeader& GetDibHeader() {
        return dib_header_;
    }
    /// BMP pixel storage getter
    ColorMatrix& GetPixelArray() {
        return pixel_array_;
    }
    /// BMP pixel storage setter
    void SetPixelArray(ColorMatrix& pixel_array) {
        pixel_array_ = pixel_array;
    }
    /// Image width(in pixels) setter
    void SetWidth(int32_t width) {
        dib_header_.width = width;
    }
    /// Image height(in pixels) setter
    void SetHeight(int32_t height) {
        dib_header_.height = height;
    }
    /// Image width(in pixels) getter
    const int32_t GetWidth() const {
        return dib_header_.width;
    }
    /// Image height(in pixels) getter
    const int32_t GetHeight() const {
        return dib_header_.height;
    }
    /// Update headers values according to the pixel storage size
    void UpdatePixelArraySizeDescription(uint32_t new_image_size);

    ~BMP(){};

private:
    BMPFileHeader file_header_;
    BMPDibHeader dib_header_;
    ColorMatrix pixel_array_;
};

#endif  // CPP_HSE_BMP_H
