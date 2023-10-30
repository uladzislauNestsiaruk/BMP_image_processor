//
// Created by vlad on 25.10.23.
//

#include <algorithm>
#include "color_matrix.h"

void ValidRgbValue(int64_t& value) {
    if (value > UINT8_MAX) {
        value = UINT8_MAX;
    }
    if (value < 0) {
        value = 0;
    }
};

ColorMatrix& ColorMatrix::operator=(const ColorMatrix& rhs) {
    if (this != &rhs) {
        height_ = rhs.height_;
        width_ = rhs.width_;
        padding_ = rhs.padding_;
        uint8_t* new_matrix = new uint8_t[2 * height_ * width_ * sizeof(Pixel) + height_ * padding_];
        std::copy(rhs.matrix_, rhs.matrix_ + height_ * width_ * sizeof(Pixel) + height_ * padding_, new_matrix);
        delete[] matrix_;
        matrix_ = new_matrix;
    }
    return *this;
}

ColorMatrix::ColorMatrix(const ColorMatrix& color_matrix) {
    width_ = color_matrix.width_;
    height_ = color_matrix.height_;
    padding_ = color_matrix.padding_;
    matrix_ = color_matrix.matrix_;
}

void ColorMatrix::Initialize(uint32_t height, uint32_t width, uint8_t padding) {
    width_ = width;
    height_ = height;
    padding_ = padding;
    matrix_ = new uint8_t[height_ * width_ * sizeof(Pixel) + height_ * padding_];
}

Pixel& Pixel::operator=(const Pixel& rhs) {
    if (this != &rhs) {
        R = rhs.R;
        G = rhs.G;
        B = rhs.B;
    }
    return *this;
}
Pixel& Pixel::operator*(const double rhs) {
    int64_t r = static_cast<int64_t>(static_cast<double>(R) * rhs);
    int64_t g = static_cast<int64_t>(static_cast<double>(G) * rhs);
    int64_t b = static_cast<int64_t>(static_cast<double>(B) * rhs);

    ValidRgbValue(r);
    ValidRgbValue(g);
    ValidRgbValue(b);

    R = static_cast<uint8_t>(r);
    G = static_cast<uint8_t>(g);
    B = static_cast<uint8_t>(b);

    return *this;
}
Pixel& Pixel::operator+(const Pixel& rhs) {
    R = UINT8_MAX - rhs.R < R ? UINT8_MAX : R + rhs.R;
    G = UINT8_MAX - rhs.G < G ? UINT8_MAX : G + rhs.G;
    B = UINT8_MAX - rhs.B < B ? UINT8_MAX : B + rhs.B;

    return *this;
}
Pixel& Pixel::operator/(const double rhs) {
    return *this * (1 / rhs);
}

Pixel ColorMatrix::GetPixel(uint32_t y, uint32_t x) {
    uint32_t total_offset = Offset(y, x);
    Pixel pixel(matrix_[total_offset], matrix_[total_offset + 1], matrix_[total_offset + 2]);
    return pixel;
}

void ColorMatrix::SetPixel(uint32_t y, uint32_t x, const Pixel& pixel) {
    uint32_t total_offset = Offset(y, x);
    matrix_[total_offset] = pixel.B;
    matrix_[total_offset + 1] = pixel.G;
    matrix_[total_offset + 2] = pixel.R;
}

const Pixel ColorMatrix::GetClosestPixel(int32_t y, int32_t x) {
    int32_t casted_height = static_cast<int32_t>(height_);
    int32_t casted_width = static_cast<int32_t>(width_);

    if (y < 0) {
        y = 0;
    }
    if (y >= casted_height) {
        y = casted_height - 1;
    }
    if (x < 0) {
        x = 0;
    }
    if (x >= casted_width) {
        x = casted_width - 1;
    }

    return GetPixel(static_cast<uint32_t>(y), static_cast<uint32_t>(x));
}

const Pixel ColorMatrix::GetCenter3X3MatrixPixel(uint32_t y, uint32_t x, const int32_t matrix[]) {
    int64_t r = 0;
    int64_t g = 0;
    int64_t b = 0;

    for (uint8_t y_coordinate = 0; y_coordinate < 3; ++y_coordinate) {
        for (uint8_t x_coordinate = 0; x_coordinate < 3; ++x_coordinate) {
            int32_t new_x_coordinate = static_cast<int32_t>(x) + x_coordinate - 1;
            int32_t new_y_coordinate = static_cast<int32_t>(y) + y_coordinate - 1;
            Pixel pixel = GetClosestPixel(new_y_coordinate, new_x_coordinate);
            r += matrix[3 * y_coordinate + x_coordinate] * pixel.R;
            g += matrix[3 * y_coordinate + x_coordinate] * pixel.G;
            b += matrix[3 * y_coordinate + x_coordinate] * pixel.B;
        }
    }

    ValidRgbValue(r);
    ValidRgbValue(g);
    ValidRgbValue(b);

    const Pixel pixel(b, g, r);
    return pixel;
}
