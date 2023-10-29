//
// Created by vlad on 28.10.23.
//

#include "pipeline.h"
void Pipeline::ApplyFilters(BMP& bmp_stream) {
    for (Filter* filter : filters_list_) {
        filter->Apply(bmp_stream);
    }
}
Pipeline::~Pipeline() {
    for (uint32_t index = 0; index < filters_list_.size(); ++index) {
        delete filters_list_[index];
    }
}
