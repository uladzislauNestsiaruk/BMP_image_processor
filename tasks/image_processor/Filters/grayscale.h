//
// Created by vlad on 27.10.23.
//

#ifndef CPP_HSE_GRAYSCALE_H
#define CPP_HSE_GRAYSCALE_H

#include "basic_filter.h"

static const double RDELTA = 0.299;
static const double GDELTA = 0.587;
static const double BDELTA = 0.114;

class GrayscaleFilter : public Filter {

public:
    explicit GrayscaleFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateGrayscaleFilter(const FilterSetting& setting) {
        return new GrayscaleFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;
};

#endif  // CPP_HSE_GRAYSCALE_H
