//
// Created by vlad on 28.10.23.
//

#ifndef CPP_HSE_FILTER_FACTORY_H
#define CPP_HSE_FILTER_FACTORY_H

#include <map>
#include <vector>

#include "Filters/basic_filter.h"
#include "Filters/edge_detection.h"
#include "Filters/crop_filter.h"
#include "Filters/blur_filter.h"
#include "Filters/grayscale.h"
#include "Filters/negative_filter.h"
#include "Filters/sharping_filter.h"
#include "pipeline.h"

using FilterProdPtr = Filter *(*)(const FilterSetting &);

class FilterFactory {

public:
    explicit FilterFactory(std::vector<FilterSetting> filters_settings_list)
        : filters_settings_list_(filters_settings_list){};
    /// Build pipeline from list of FilterSettings
    const Pipeline BuildPipeline();

private:
    std::vector<FilterSetting> filters_settings_list_;
    /// map to match filter name with filter create function
    ///!!!IF YOU WANT TO ADD YOUR OWN FUNCTION YOU HAVE TO ADD SUCH MATCHING TO THIS MAP
    std::map<std::string, FilterProdPtr> filters_list_{{"crop", CropFilter::CreateCropFilter},
                                                       {"blur", BlurFilter::CreateBlurFilter},
                                                       {"edge", EdgeDetectionFilter::CreateEdgeDetectionFilter},
                                                       {"gs", GrayscaleFilter::CreateGrayscaleFilter},
                                                       {"neg", NegativeFilter::CreateNegativeFilter},
                                                       {"sharp", SharpingFilter::CreateSharpingFilter}};
};

#endif  // CPP_HSE_FILTER_FACTORY_H
