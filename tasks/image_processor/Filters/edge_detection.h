//
// Created by vlad on 28.10.23.
//

#ifndef CPP_HSE_EDGE_DETECTION_H
#define CPP_HSE_EDGE_DETECTION_H

#include "basic_filter.h"

class EdgeDetectionFilter : public Filter {

public:
    const static uint16_t PARAMETERS_AMOUNT = 1;

    explicit EdgeDetectionFilter(FilterSetting setting) : Filter(setting) {
    }

    static Filter* CreateEdgeDetectionFilter(const FilterSetting& setting) {
        return new EdgeDetectionFilter(setting);
    }

    void Apply(BMP& bmp_stream) override;

private:
    constexpr static int32_t EdgeDetectionFilterMatrix[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
};

#endif  // CPP_HSE_EDGE_DETECTION_H
