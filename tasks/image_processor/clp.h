//
// Created by vlad on 26.10.23.
//

#ifndef CPP_HSE_CLP_H
#define CPP_HSE_CLP_H

#include <vector>
#include <map>

#include "filter_setting.h"

class CLP {

public:
    CLP() {
    }

    /// Checks that char sequence represents a filter name
    bool IsFilterName(char* line) {
        return line[0] == '-';
    }
    /// Extracts filter name from char sequence
    std::string GetFilterName(char* line);
    /// Set parameters from vector to the FilterSetting object
    void SetParameters(FilterSetting& filter_setting, std::vector<char*> parameters);
    /// Checks that filter ith such FilterSetting can exist.
    bool IsFilterSettingCorrect(const FilterSetting& filter_setting);
    /// Checks correctness of each FilterSetting objects
    void FiltersSettingsVerification(std::vector<FilterSetting>& filters_setting);
    /// Convert command line arguments to vector of correct FilterSetting objects, save input and output files paths
    std::vector<FilterSetting> ParametersToFilterSetting(int parameters_amount, char* arguments[],
                                                         std::string& input_file, std::string& output_file);

private:
    std::map<std::string, uint8_t> filters_description_ = {{"crop", 2},  {"gs", 0},   {"neg", 0},
                                                           {"sharp", 0}, {"edge", 1}, {"blur", 1}};
};
#endif  // CPP_HSE_CLP_H
