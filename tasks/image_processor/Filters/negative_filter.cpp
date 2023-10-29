//
// Created by vlad on 27.10.23.
//

#include "negative_filter.h"

void NegativeFilter::apply(BMP& bmp_stream) {
    for (int32_t y_coordinate = 0; y_coordinate < bmp_stream.GetDibHeader().height; ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < bmp_stream.GetDibHeader().width; ++x_coordinate) {
            Pixel pixel = bmp_stream.GetPixelArray().GetPixel(y_coordinate, x_coordinate);

            pixel.R = UINT8_MAX - pixel.R;
            pixel.G = UINT8_MAX - pixel.G;
            pixel.B = UINT8_MAX - pixel.B;

            bmp_stream.GetPixelArray().SetPixel(y_coordinate, x_coordinate, pixel);
        }
    }
}
