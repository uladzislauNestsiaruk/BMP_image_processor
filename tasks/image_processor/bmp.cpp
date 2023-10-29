//
// Created by vlad on 29.10.23.
//

#include "bmp.h"

void BMP::UpdatePixelArraySizeDescription(uint32_t new_image_size) {
    dib_header_.image_size = 0;
    file_header_.file_size = BMP_FILE_HEADER_SIZE + dib_header_.size + new_image_size;
}