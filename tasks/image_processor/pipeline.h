//
// Created by vlad on 28.10.23.
//

#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include <vector>

#include "Filters/basic_filter.h"

class Pipeline {

public:
    Pipeline(){};

    explicit Pipeline(std::vector<Filter*> filters_list) : filters_list_(filters_list) {
    }
    // Function to apply list of filters to the image
    void ApplyFilters(BMP& bmp_stream);

    ~Pipeline();

private:
    std::vector<Filter*> filters_list_;
};

#endif  // CPP_HSE_PIPELINE_H
