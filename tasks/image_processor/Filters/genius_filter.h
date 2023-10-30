//
// Created by vlad on 30.10.23.
//

#ifndef CPP_HSE_GENIUS_FILTER_H
#define CPP_HSE_GENIUS_FILTER_H

#include "basic_filter.h"
#include "blur_filter.h"
#include "negative_filter.h"

class GeniusFilter : public Filter {

public:
    const static uint16_t PARAMETERS_AMOUNT = 1;

    explicit GeniusFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateGeniusFilter(const FilterSetting& setting) {
        return new GeniusFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;

private:
    /// Checks is pixel can be a part of circuit
    bool IsLargerThanThreshold(int32_t y_coordinate, int32_t x_coordinate, BMP& bmp_stream, uint8_t threshold);

    constexpr static int32_t NeighbourPixelsMatrix[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    constexpr static int32_t GradientX[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    constexpr static int32_t GradientY[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
};

#endif  // CPP_HSE_GENIUS_FILTER_H
