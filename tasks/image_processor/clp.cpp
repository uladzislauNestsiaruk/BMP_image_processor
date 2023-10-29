//
// Created by vlad on 26.10.23.
//


#include "clp.h"
#include <vector>
#include <stdexcept>
#include <map>

static std::map<std::string, uint8_t> filters_description = {
    {"crop", 2},
    {"gs", 0},
    {"neg", 0},
    {"sharp", 0},
    {"edge", 1},
    {"blur", 1}
};

std::string CLP::GetFilterName(char* line) {
     std::string filter_name = line;
     filter_name.erase(filter_name.begin());
     return filter_name;
}

void CLP::SetParameters(FilterSetting& filter_setting, std::vector<char*> parameters) {
    std::string* parameters_list = new std::string[parameters.size()];
    for(size_t index = 0; index < parameters.size(); ++index){
        parameters_list[index] = parameters[index];
    }
    filter_setting.SetParameters(parameters_list, parameters.size());
}

bool CLP::IsFilterSettingCorrect(const FilterSetting& filter_setting) {
    if(!filters_description.contains(filter_setting.GetFilterName())){
        throw std::runtime_error("Unknown filter name used.");
    }
    if(filters_description[filter_setting.GetFilterName()] != filter_setting.GetFilterParametersAmount()){
        throw std::runtime_error("Incorrect parameters amount for a particular filter.");
    }
    return true;
}

void CLP::FiltersSettingsVerification(std::vector<FilterSetting>& filters_settings) {
    std::vector<FilterSetting> correct_filters_settings;
    for(const FilterSetting& filter_setting : filters_settings){
        if(IsFilterSettingCorrect(filter_setting)){
            correct_filters_settings.emplace_back(filter_setting);
        }
    }
    filters_settings = correct_filters_settings;
}

std::vector<FilterSetting> CLP::ParametersToFilterSetting(int parameters_amount, char* arguments[], std::string& input_file,
                                                          std::string& output_file) {
    std::vector<FilterSetting> filters_settings;
    std::vector<char*> unprocessed_parameters;
    if(parameters_amount < 3){
        throw std::runtime_error("to low amount of arguments.");
    }

    input_file = arguments[1];
    output_file = arguments[2];

    for(int32_t index = 3; index < parameters_amount; ++index){
        if(IsFilterName(arguments[index])){
            if(!filters_settings.empty()){
                SetParameters(filters_settings.back(), unprocessed_parameters);
                unprocessed_parameters.clear();
            }
            filters_settings.emplace_back(FilterSetting(GetFilterName(arguments[index])));
        } else{
            unprocessed_parameters.emplace_back(arguments[index]);
        }
    }

    if(!filters_settings.empty()){
        SetParameters(filters_settings.back(), unprocessed_parameters);
        unprocessed_parameters.clear();
    }

    FiltersSettingsVerification(filters_settings);
    return filters_settings;
}
