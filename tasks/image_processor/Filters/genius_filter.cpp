//
// Created by vlad on 30.10.23.
//

#include <complex>
#include "genius_filter.h"

Pixel GetMagnitude(Pixel& x_gradient, Pixel& y_gradient) {
    double x_r = static_cast<double>(x_gradient.R);
    double x_g = static_cast<double>(x_gradient.G);
    double x_b = static_cast<double>(x_gradient.B);

    double y_r = static_cast<double>(y_gradient.R);
    double y_g = static_cast<double>(y_gradient.G);
    double y_b = static_cast<double>(y_gradient.B);

    uint8_t r = static_cast<uint8_t>(std::sqrt(x_r * x_r + y_r * y_r));
    uint8_t g = static_cast<uint8_t>(std::sqrt(x_g * x_g + y_g * y_g));
    uint8_t b = static_cast<uint8_t>(std::sqrt(x_b * x_b + y_b * y_b));

    return Pixel(b, g, r);
}

bool GeniusFilter::IsLargerThanThreshold(int32_t y_coordinate, int32_t x_coordinate, BMP& bmp_stream,
                                         uint8_t threshold) {
    Pixel new_pixel_x =
        bmp_stream.GetPixelArray().GetCenter3X3MatrixPixel(y_coordinate, x_coordinate, GeniusFilter::GradientX);
    Pixel new_pixel_y = bmp_stream.GetPixelArray().GetCenter3X3MatrixPixel(y_coordinate, x_coordinate, GradientY);
    Pixel magnitude = GetMagnitude(new_pixel_x, new_pixel_y);
    double intensity =
        (static_cast<double>(magnitude.R) + static_cast<double>(magnitude.G) + static_cast<double>(magnitude.B)) / 3;

    return intensity > threshold;
}

void GeniusFilter::Apply(BMP& bmp_stream) {

    double threshold = std::stod(setting_.GetFilterParameter(0));
    threshold = UINT8_MAX * threshold;

    ColorMatrix new_matrix;
    new_matrix.Initialize(bmp_stream.GetDibHeader().height, bmp_stream.GetDibHeader().width,
                          bmp_stream.GetPixelArray().GetPadding());

    for (int32_t y_coordinate = 0; y_coordinate < bmp_stream.GetDibHeader().height; ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < bmp_stream.GetDibHeader().width; ++x_coordinate) {
            Pixel pixel = bmp_stream.GetPixelArray().GetPixel(y_coordinate, x_coordinate);
            if (IsLargerThanThreshold(y_coordinate, x_coordinate, bmp_stream, static_cast<uint8_t>(threshold))) {
                pixel = Pixel(0, 0, 0);
            }

            new_matrix.SetPixel(y_coordinate, x_coordinate, pixel);
        }
    }

    bmp_stream.SetPixelArray(new_matrix);

    const double pixel_divisor = 9;
    const double colors_redution_reps = 10;

    for (int reps = 0; reps < colors_redution_reps; ++reps) {
        for (int32_t y_coordinate = 0; y_coordinate < bmp_stream.GetDibHeader().height; ++y_coordinate) {
            for (int32_t x_coordinate = 0; x_coordinate < bmp_stream.GetDibHeader().width; ++x_coordinate) {
                if (!IsLargerThanThreshold(y_coordinate, x_coordinate, bmp_stream, static_cast<uint8_t>(threshold))) {
                    continue;
                }
                std::tuple<double, double, double> double_pixel =
                    bmp_stream.GetPixelArray().GetCenter3X3MatrixDoublePixel(y_coordinate, x_coordinate,
                                                                             NeighbourPixelsMatrix);
                Pixel pixel;
                pixel.R = static_cast<uint8_t>(static_cast<double>(get<2>(double_pixel)) / pixel_divisor);
                pixel.G = static_cast<uint8_t>(static_cast<double>(get<1>(double_pixel)) / pixel_divisor);
                pixel.B = static_cast<uint8_t>(static_cast<double>(get<0>(double_pixel)) / pixel_divisor);
                new_matrix.SetPixel(x_coordinate, y_coordinate, pixel);
            }
        }
        bmp_stream.SetPixelArray(new_matrix);
    }
}
