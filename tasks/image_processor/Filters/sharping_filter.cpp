//
// Created by vlad on 27.10.23.
//

#include "sharping_filter.h"
void SharpingFilter::Apply(BMP& bmp_stream) {
    ColorMatrix new_matrix;
    new_matrix.Initialize(bmp_stream.GetDibHeader().height, bmp_stream.GetDibHeader().width,
                          bmp_stream.GetPixelArray().GetPadding());
    for (int32_t y_coordinate = 0; y_coordinate < bmp_stream.GetDibHeader().height; ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < bmp_stream.GetDibHeader().width; ++x_coordinate) {
            Pixel new_pixel = bmp_stream.GetPixelArray().GetCenter3X3MatrixPixel(y_coordinate, x_coordinate,
                                                                                 SharpingFilter::SharpingFilterMatrix);
            new_matrix.SetPixel(y_coordinate, x_coordinate, new_pixel);
        }
    }
    bmp_stream.GetPixelArray() = new_matrix;
}
