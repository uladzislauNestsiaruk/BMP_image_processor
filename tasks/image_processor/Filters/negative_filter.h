//
// Created by vlad on 27.10.23.
//

#ifndef CPP_HSE_NEGATIVE_FILTER_H
#define CPP_HSE_NEGATIVE_FILTER_H

#include "basic_filter.h"

class NegativeFilter : public Filter{

public:

    explicit NegativeFilter(FilterSetting setting) : Filter(setting){}

    static Filter* CreateNegativeFilter(const FilterSetting& setting){return new NegativeFilter(setting);}

    void apply(BMPStream& bmp_stream) override;

};

#endif  // CPP_HSE_NEGATIVE_FILTER_H
