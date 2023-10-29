//
// Created by vlad on 28.10.23.
//

#ifndef CPP_HSE_EDGE_DETECTION_H
#define CPP_HSE_EDGE_DETECTION_H

#include "basic_filter.h"

const static int32_t EDGE_DETECTION_FILTER_MATRIX[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};

class EdgeDetectionFilter : public Filter {

public:
    explicit EdgeDetectionFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateEdgeDetectionFilter(const FilterSetting& setting) {
        return new EdgeDetectionFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;
};

#endif  // CPP_HSE_EDGE_DETECTION_H
