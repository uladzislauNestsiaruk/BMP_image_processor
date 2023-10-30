//
// Created by vlad on 28.10.23.
//

#ifndef CPP_HSE_BLUR_FILTER_H
#define CPP_HSE_BLUR_FILTER_H

#include <valarray>

#include "basic_filter.h"

class BlurFilter : public Filter {

public:
    static const uint16_t PARAMETERS_AMOUNT = 1;
    static const int32_t FILTER_SIGMA_COEFFICIENT = 3;
    const double PI = 3.14159265358979323846264338327950;
    const double E = 2.71828182846;
    const double MAXIMUM_SIGMA_VALUE = 150;

    explicit BlurFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateBlurFilter(const FilterSetting& setting) {
        return new BlurFilter(setting);
    }

    ///!!!IF FILTER HAS AT LEAST ONE PARAMETER YOU HAVE TO WRITE YOUR OWN METHOD CHECKING THEIR CORRECTNESS
    void IsParametersCorrect(const FilterSetting& setting) override;

    void Apply(BMP& bmp_stream) override;
};

#endif  // CPP_HSE_BLUR_FILTER_H
