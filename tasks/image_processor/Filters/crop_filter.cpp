//
// Created by vlad on 26.10.23.
//

#include "crop_filter.h"

void CropFilter::Apply(BMP& bmp) {
    int32_t new_width = std::stoi(setting_.GetFilterParameter(0));
    int32_t new_height = std::stoi(setting_.GetFilterParameter(1));

    new_width = std::min(new_width, bmp.GetWidth());
    new_height = std::min(new_height, bmp.GetHeight());
    uint8_t new_padding = (4 - (new_width * sizeof(Pixel)) % 4) % 4;

    ColorMatrix pixel_array;
    pixel_array.Initialize(new_height, new_width, new_padding);

    int32_t start_y_point = bmp.GetDibHeader().height - new_height;

    for (int32_t y_coordinate = start_y_point; y_coordinate < bmp.GetHeight(); ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < new_width; ++x_coordinate) {
            Pixel pixel = bmp.GetPixelArray().GetPixel(y_coordinate, x_coordinate);
            pixel_array.SetPixel(y_coordinate - start_y_point, x_coordinate, pixel);
        }
    }

    uint32_t bytes_per_row = bmp.GetDibHeader().bit_per_pixel * new_width + new_padding;
    uint32_t new_image_size = bytes_per_row * new_height;

    bmp.SetWidth(new_width);
    bmp.SetHeight(new_height);

    bmp.UpdatePixelArraySizeDescription(new_image_size);

    bmp.SetPixelArray(pixel_array);
}
