//
// Created by vlad on 27.10.23.
//

#ifndef CPP_HSE_NEGATIVE_FILTER_H
#define CPP_HSE_NEGATIVE_FILTER_H

#include "basic_filter.h"

class NegativeFilter : public Filter {

public:
    const static uint16_t PARAMETERS_AMOUNT = 0;

    explicit NegativeFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateNegativeFilter(const FilterSetting& setting) {
        return new NegativeFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;
};

#endif  // CPP_HSE_NEGATIVE_FILTER_H
