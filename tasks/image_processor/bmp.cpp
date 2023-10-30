//
// Created by vlad on 29.10.23.
//

#include "bmp.h"

void BMP::UpdatePixelArraySizeDescription(uint32_t new_image_size) {
    dib_header_.image_size = 0;
    // recalculate pixel storage size
    file_header_.file_size = sizeof(BMPFileHeader) + sizeof(BMPDibHeader) + new_image_size;
}