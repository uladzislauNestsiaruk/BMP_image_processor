//
// Created by vlad on 28.10.23.
//

#include "pipeline.h"
#include "filter_factory .h"

const Pipeline FilterFactory::BuildPipeline() {
    std::vector<Filter*> filters;
    for (const FilterSetting& setting : filters_settings_list_) {
        std::string filter_name = setting.GetFilterName();
        Filter* filter = filters_list[filter_name](setting);
        filters.emplace_back(filter);
    }

    const Pipeline pipeline(filters);
    return pipeline;
}
