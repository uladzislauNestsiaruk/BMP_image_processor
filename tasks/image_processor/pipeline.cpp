//
// Created by vlad on 28.10.23.
//

#include "pipeline.h"
void Pipeline::ApplyFilters(BMP& bmp_stream) {
    for (Filter* filter : filters_list_) {
        filter->apply(bmp_stream);
    }
}
