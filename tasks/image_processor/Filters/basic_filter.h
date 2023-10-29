//
// Created by vlad on 26.10.23.
//

#ifndef CPP_HSE_BASIC_FILTER_H
#define CPP_HSE_BASIC_FILTER_H

#include "../filter_setting.h"
#include "../bmp_stream.h"

class Filter{

public:

    Filter(){};

    explicit Filter(const FilterSetting& setting) : setting_(setting){}

    virtual void apply(BMPStream& bmp_stream);

protected:

   FilterSetting setting_;

};
#endif  // CPP_HSE_BASIC_FILTER_H
