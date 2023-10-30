//
// Created by vlad on 28.10.23.
//

#include "pipeline.h"
#include "filter_factory.h"

const Pipeline FilterFactory::BuildPipeline() {
    std::vector<Filter*> filters;
    // convert list of FilterSettings to list of Filters
    for (const FilterSetting& setting : filters_settings_list_) {
        std::string filter_name = setting.GetFilterName();
        Filter* filter = FilterFactory::filters_list_[filter_name](setting);
        filters.emplace_back(filter);
    }
    // Build pipeline
    const Pipeline pipeline(filters);
    return pipeline;
}
