//
// Created by vlad on 27.10.23.
//

#ifndef CPP_HSE_SHARPING_FILTER_H
#define CPP_HSE_SHARPING_FILTER_H

#include "basic_filter.h"

const static int32_t SHARPING_FILTER_MATRIX[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};

class SharpingFilter : public Filter{

public:

    explicit SharpingFilter(FilterSetting setting) : Filter(setting){}

    static Filter* CreateSharpingFilter(const FilterSetting& setting){return new SharpingFilter(setting);}

    void apply(BMPStream& bmp_stream) override;

};

#endif  // CPP_HSE_SHARPING_FILTER_H
