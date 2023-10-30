//
// Created by vlad on 28.10.23.
//

#include "blur_filter.h"

struct DoublePixel {
    long double R = 0;
    long double G = 0;
    long double B = 0;
};

const DoublePixel GetKernelMatrixValueHorizontal(int32_t y, int32_t x, ColorMatrix& matrix, double sigma,
                                                 long double* e_array) {
    int32_t dst = static_cast<int32_t>(BlurFilter::FILTER_SIGMA_COEFFICIENT * sigma);

    DoublePixel pixel;

    for (int32_t x_coordinate = x - dst; x_coordinate <= x + dst; ++x_coordinate) {
        int32_t actual_x = std::max(0, std::min(static_cast<int32_t>(matrix.GetWidth()) - 1, x_coordinate));
        Pixel window_pixel = matrix.GetPixel(y, actual_x);
        long double divisor = e_array[abs(x - x_coordinate)];
        pixel.R += static_cast<long double>(window_pixel.R) / divisor;
        pixel.G += static_cast<long double>(window_pixel.G) / divisor;
        pixel.B += static_cast<long double>(window_pixel.B) / divisor;
    }

    return pixel;
}

const DoublePixel GetKernelMatrixValueVertical(int32_t y, int32_t x, long double** matrix, double sigma, int32_t height,
                                               long double* e_array) {
    int32_t dst = static_cast<int32_t>(BlurFilter::FILTER_SIGMA_COEFFICIENT * sigma);

    DoublePixel pixel;

    for (int32_t y_coordinate = y - dst; y_coordinate <= y + dst; ++y_coordinate) {
        int32_t actual_y = std::max(0, std::min(height - 1, y_coordinate));
        pixel.B += matrix[actual_y][3 * x] / e_array[abs(y - y_coordinate)];
        pixel.G += matrix[actual_y][3 * x + 1] / e_array[abs(y - y_coordinate)];
        pixel.R += matrix[actual_y][3 * x + 2] / e_array[abs(y - y_coordinate)];
    }

    return pixel;
}

Pixel CastDoublePixel(DoublePixel pixel) {
    uint8_t b = pixel.B > UINT8_MAX ? UINT8_MAX : static_cast<uint8_t>(pixel.B);
    uint8_t g = pixel.G > UINT8_MAX ? UINT8_MAX : static_cast<uint8_t>(pixel.G);
    uint8_t r = pixel.R > UINT8_MAX ? UINT8_MAX : static_cast<uint8_t>(pixel.R);

    return Pixel(b, g, r);
}

void BlurFilter::Apply(BMP& bmp_stream) {
    double sigma = std::stod(setting_.GetFilterParameter(0));
    long double* e_array = new long double[static_cast<int32_t>(FILTER_SIGMA_COEFFICIENT * sigma) + 1];

    for (int32_t dst = 0; dst <= static_cast<int32_t>(FILTER_SIGMA_COEFFICIENT * sigma); ++dst) {
        double power = static_cast<double>(dst * dst) / 2 / sigma / sigma;
        e_array[dst] = pow(E, power);
    }

    int32_t height = bmp_stream.GetDibHeader().height;
    int32_t width = bmp_stream.GetDibHeader().width;

    long double** horizontal_matrix = new long double*[height];

    double multiplier = 1.0 / sigma / sigma / 2 / PI;

    for (int32_t y_coordinate = 0; y_coordinate < height; ++y_coordinate) {
        horizontal_matrix[y_coordinate] = new long double[3 * width];
        for (int32_t x_coordinate = 0; x_coordinate < width; ++x_coordinate) {
            DoublePixel pixel =
                GetKernelMatrixValueHorizontal(y_coordinate, x_coordinate, bmp_stream.GetPixelArray(), sigma, e_array);
            horizontal_matrix[y_coordinate][x_coordinate * 3] = pixel.B;
            horizontal_matrix[y_coordinate][x_coordinate * 3 + 1] = pixel.G;
            horizontal_matrix[y_coordinate][x_coordinate * 3 + 2] = pixel.R;
        }
    }

    for (int32_t y_coordinate = 0; y_coordinate < height; ++y_coordinate) {
        for (int32_t x_coordinate = 0; x_coordinate < width; ++x_coordinate) {
            DoublePixel pixel =
                GetKernelMatrixValueVertical(y_coordinate, x_coordinate, horizontal_matrix, sigma, height, e_array);
            pixel.R *= multiplier;
            pixel.G *= multiplier;
            pixel.B *= multiplier;
            bmp_stream.GetPixelArray().SetPixel(y_coordinate, x_coordinate, CastDoublePixel(pixel));
            Pixel temp = bmp_stream.GetPixelArray().GetPixel(y_coordinate, x_coordinate);
            if (temp.R == pixel.R) {
                temp.R = 1;
            }
        }
    }

    for (int32_t y_coordinate = 0; y_coordinate < height; ++y_coordinate) {
        delete[] horizontal_matrix[y_coordinate];
    }

    delete[] e_array;
    delete[] horizontal_matrix;
}
