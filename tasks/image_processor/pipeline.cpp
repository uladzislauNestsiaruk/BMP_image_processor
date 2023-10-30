//
// Created by vlad on 28.10.23.
//

#include <iostream>
#include "pipeline.h"
void Pipeline::ApplyFilters(BMP& bmp_stream) {
    for (Filter* filter : filters_list_) {
        try {
            filter->Apply(bmp_stream);
        } catch (std::exception& e) {
            std::cerr << "Filter was skipped due to the incorrect parameters.\n";
        } catch (...) {
            std::cerr << "Unknown error during filter usage.\n";
        }
    }
}
Pipeline::~Pipeline() {
    for (uint32_t index = 0; index < filters_list_.size(); ++index) {
        delete filters_list_[index];
    }
}
