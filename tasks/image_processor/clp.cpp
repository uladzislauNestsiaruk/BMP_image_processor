//
// Created by vlad on 26.10.23.
//

#include "clp.h"
#include <vector>
#include <stdexcept>

std::string CLP::GetFilterName(char* line) {
    std::string filter_name = line;
    filter_name.erase(filter_name.begin());
    return filter_name;
}

bool CLP::IsFilterSettingCorrect(const FilterSetting& filter_setting) {
    if (!CLP::filters_description_.contains(filter_setting.GetFilterName())) {
        throw std::runtime_error("Unknown filter name used.");
    }
    if (CLP::filters_description_[filter_setting.GetFilterName()] != filter_setting.GetFilterParameters().size()) {
        throw std::runtime_error("Incorrect parameters amount for a particular filter.");
    }
    return true;
}

void CLP::FiltersSettingsVerification(std::vector<FilterSetting>& filters_settings) {
    std::vector<FilterSetting> correct_filters_settings;
    for (const FilterSetting& filter_setting : filters_settings) {
        if (IsFilterSettingCorrect(filter_setting)) {
            correct_filters_settings.emplace_back(filter_setting);
        }
    }
    filters_settings = correct_filters_settings;
}

std::vector<FilterSetting> CLP::ParametersToFilterSetting(int parameters_amount, char* arguments[],
                                                          std::string& input_file, std::string& output_file) {
    std::vector<FilterSetting> filters_settings;
    std::vector<std::string> unprocessed_parameters;
    if (parameters_amount < 3) {
        throw std::runtime_error("to low amount of arguments.");
    }

    input_file = arguments[1];
    output_file = arguments[2];

    for (int32_t index = 3; index < parameters_amount; ++index) {
        if (IsFilterName(arguments[index])) {
            if (!filters_settings.empty()) {
                filters_settings.back().SetFilterParameters(unprocessed_parameters);
                unprocessed_parameters.clear();
            }
            filters_settings.emplace_back(FilterSetting(GetFilterName(arguments[index])));
        } else {
            unprocessed_parameters.emplace_back(arguments[index]);
        }
    }

    if (!filters_settings.empty()) {
        filters_settings.back().SetFilterParameters(unprocessed_parameters);
        unprocessed_parameters.clear();
    }

    FiltersSettingsVerification(filters_settings);
    return filters_settings;
}
