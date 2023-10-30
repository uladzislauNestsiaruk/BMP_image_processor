//
// Created by vlad on 26.10.23.
//

#include "clp.h"
#include <vector>
#include <stdexcept>
#include <iostream>

bool CLP::CheckIsInputPathCorrect(const std::string& path) {
    std::ifstream stream(path);
    return !!stream;
}

bool CLP::CheckIsOutputPathCorrect(const std::string& path) {
    std::ofstream stream(path);
    return !!stream;
}

std::string CLP::GetFilterName(char* line) {
    std::string filter_name = line;
    filter_name.erase(filter_name.begin());
    return filter_name;
}

bool CLP::IsFilterSettingCorrect(const FilterSetting& filter_setting) {
    // Check is filter with such name exists.
    if (!CLP::filters_description_.contains(filter_setting.GetFilterName())) {
        throw std::runtime_error("Unknown filter name used.");
    }
    // Check is amount of parameters for particular filter correct.
    if (CLP::filters_description_[filter_setting.GetFilterName()] != filter_setting.GetFilterParameters().size()) {
        throw std::runtime_error("Incorrect parameters amount for a particular filter.");
    }
    return true;
}

void CLP::FiltersSettingsVerification(std::vector<FilterSetting>& filters_settings) {
    std::vector<FilterSetting> correct_filters_settings;
    for (const FilterSetting& filter_setting : filters_settings) {
        // Trying to add filter description to list if it's correct
        try {
            IsFilterSettingCorrect(filter_setting);
            correct_filters_settings.emplace_back(filter_setting);
        } catch (std::exception& e) {
            std::cerr
                << "Used filter with wrong name or wrong amount of parameters at particular filter so it's skipped.\n";
        } catch (...) {
            std::cerr << "Unknown error.\n";
        }
    }
    filters_settings = correct_filters_settings;
}

std::vector<FilterSetting> CLP::ParametersToFilterSetting(int parameters_amount, char* arguments[],
                                                          std::string& input_file, std::string& output_file) {
    std::vector<FilterSetting> filters_settings;
    std::vector<std::string> unprocessed_parameters;
    // Check for minimum amount of command line parameters
    if (parameters_amount < 3) {
        throw std::runtime_error("to low amount of arguments.");
    }

    input_file = arguments[1];
    output_file = arguments[2];
    // Check is input and output file paths correct
    if (!CheckIsInputPathCorrect(input_file)) {
        throw std::runtime_error("input file path incorrect.");
    }
    if (!CheckIsOutputPathCorrect(output_file)) {
        throw std::runtime_error("output file path incorrect.");
    }

    for (int32_t index = 3; index < parameters_amount; ++index) {
        // separate filter names and filter arguments
        if (IsFilterName(arguments[index])) {
            // if it's filter we add it to the list
            if (!filters_settings.empty()) {
                // if it's not first filter add his discription
                filters_settings.back().SetFilterParameters(unprocessed_parameters);
                unprocessed_parameters.clear();
            }
            filters_settings.emplace_back(FilterSetting(GetFilterName(arguments[index])));
        } else {
            // otherwise add new filter argument to unprocessed list
            unprocessed_parameters.emplace_back(arguments[index]);
        }
    }
    // additional case for the last filter
    if (!filters_settings.empty()) {
        filters_settings.back().SetFilterParameters(unprocessed_parameters);
        unprocessed_parameters.clear();
    }
    // Verify basic correctness of extracted filters
    FiltersSettingsVerification(filters_settings);
    return filters_settings;
}
