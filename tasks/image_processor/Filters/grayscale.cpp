//
// Created by vlad on 27.10.23.
//

#include "grayscale.h"
void GrayscaleFilter::Apply(BMP& bmp_stream) {
    for (int32_t y_coordinate = 0; y_coordinate < bmp_stream.GetDibHeader().height; ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < bmp_stream.GetDibHeader().width; ++x_coordinate) {
            Pixel pixel = bmp_stream.GetPixelArray().GetPixel(y_coordinate, x_coordinate);

            uint8_t pixel_value =
                static_cast<uint8_t>(RDELTA * static_cast<double>(pixel.R) + BDELTA * static_cast<double>(pixel.B) +
                                     GDELTA * static_cast<double>(pixel.G));

            pixel.R = pixel_value;
            pixel.G = pixel_value;
            pixel.B = pixel_value;

            bmp_stream.GetPixelArray().SetPixel(y_coordinate, x_coordinate, pixel);
        }
    }
}
