//
// Created by vlad on 27.10.23.
//

#ifndef CPP_HSE_SHARPING_FILTER_H
#define CPP_HSE_SHARPING_FILTER_H

#include "basic_filter.h"

class SharpingFilter : public Filter {

public:
    const static uint16_t PARAMETERS_AMOUNT = 0;

    explicit SharpingFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateSharpingFilter(const FilterSetting& setting) {
        return new SharpingFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;

private:
    constexpr static int32_t SharpingFilterMatrix[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};

#endif  // CPP_HSE_SHARPING_FILTER_H
