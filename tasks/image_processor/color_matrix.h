//
// Created by vlad on 25.10.23.
//

#ifndef CPP_HSE_COLOR_MATRIX_H
#define CPP_HSE_COLOR_MATRIX_H

#include <cstdint>
#include <tuple>

static const uint8_t MATRIX3X3SIZE = 9;  // Wow, NOW IT'S NOT A MAGIC NUMBER!!!!!

struct Pixel {

    Pixel() : B(0), G(0), R(0){};

    Pixel(uint8_t b, uint8_t g, uint8_t r) : B(b), G(g), R(r) {
    }

    Pixel& operator=(const Pixel& rhs);

    Pixel& operator*(const double rhs);

    Pixel& operator+(const Pixel& rhs);

    Pixel& operator/(const double rhs);

    uint8_t B;
    uint8_t G;
    uint8_t R;
} __attribute__((packed));

class ColorMatrix {
public:
    ColorMatrix() {
    }

    ColorMatrix(uint32_t height, uint32_t width) : width_(width), height_(height) {
    }

    ColorMatrix(const ColorMatrix&);

    ColorMatrix& operator=(const ColorMatrix& rhs);

    void Initialize(uint32_t height, uint32_t width, uint8_t padding);

    const uint32_t Offset(uint32_t y, uint32_t x) const {
        return y * (width_ * sizeof(Pixel) + padding_) + x * sizeof(Pixel);
    }

    uint8_t& GetPixelMatrix() {
        return *matrix_;
    }

    uint8_t GetPadding() const {
        return padding_;
    }

    const uint32_t GetHeight() const {
        return height_;
    }

    const uint32_t GetWidth() const {
        return width_;
    }

    Pixel GetPixel(uint32_t x, uint32_t y);

    const Pixel GetCenter3X3MatrixPixel(uint32_t x, uint32_t y, const int32_t matrix[]);

    const std::tuple<double, double, double> GetCenter3X3MatrixDoublePixel(uint32_t x, uint32_t y,
                                                                           const int32_t matrix[]);

    void SetPixel(uint32_t x, uint32_t y, const Pixel& pixel);

    ~ColorMatrix();

private:
    const Pixel GetClosestPixel(int32_t x, int32_t y);

    uint32_t width_ = 0;
    uint32_t height_ = 0;
    uint8_t padding_;
    uint8_t* matrix_;
};

#endif  // CPP_HSE_COLOR_MATRIX_H
