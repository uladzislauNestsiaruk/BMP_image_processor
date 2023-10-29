//
// Created by vlad on 28.10.23.
//

#ifndef CPP_HSE_BLUR_FILTER_H
#define CPP_HSE_BLUR_FILTER_H

#include <valarray>

#include "basic_filter.h"

class BlurFilter : public Filter {

public:
    static const int32_t FILTER_SIGMA_COEFFICIENT = 3;
    const double PI = 3.14159265358979323846264338327950;
    const double E = 2.71828182846;

    explicit BlurFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateBlurFilter(const FilterSetting& setting) {
        return new BlurFilter(setting);
    }

    void apply(BMP& bmp_stream) override;
};

#endif  // CPP_HSE_BLUR_FILTER_H
