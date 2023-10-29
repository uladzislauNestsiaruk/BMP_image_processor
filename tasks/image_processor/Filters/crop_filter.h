//
// Created by vlad on 26.10.23.
//

#ifndef CPP_HSE_CROP_FILTER_H
#define CPP_HSE_CROP_FILTER_H

#include "basic_filter.h"

class CropFilter : public Filter {

public:
    explicit CropFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateCropFilter(const FilterSetting& setting) {
        return new CropFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;
};

#endif  // CPP_HSE_CROP_FILTER_H
