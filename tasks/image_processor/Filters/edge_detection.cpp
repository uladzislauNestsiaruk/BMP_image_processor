//
// Created by vlad on 28.10.23.
//

#include "edge_detection.h"

void EdgeDetectionFilter::Apply(BMP& bmp_stream) {
    double double_threshold = std::stod(setting_.GetFilterParameter(0));
    uint8_t threshold = static_cast<uint8_t>(static_cast<double>(UINT8_MAX) * double_threshold);

    ColorMatrix new_matrix;
    new_matrix.Initialize(bmp_stream.GetDibHeader().height, bmp_stream.GetDibHeader().width,
                          bmp_stream.GetPixelArray().GetPadding());
    for (int32_t y_coordinate = 0; y_coordinate < bmp_stream.GetDibHeader().height; ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < bmp_stream.GetDibHeader().width; ++x_coordinate) {
            Pixel new_pixel = bmp_stream.GetPixelArray().GetCenter3X3MatrixPixel(y_coordinate, x_coordinate,
                                                                                 EdgeDetectionFilterMatrix);

            if (std::max({new_pixel.B, new_pixel.R, new_pixel.G}) >= threshold) {
                new_pixel = Pixel(UINT8_MAX, UINT8_MAX, UINT8_MAX);
            } else {
                new_pixel = Pixel(0, 0, 0);
            }

            new_matrix.SetPixel(y_coordinate, x_coordinate, new_pixel);
        }
    }
    bmp_stream.GetPixelArray() = new_matrix;
}
