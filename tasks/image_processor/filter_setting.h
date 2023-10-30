//
// Created by vlad on 26.10.23.
//

#ifndef CPP_HSE_FILTER_SETTING_H
#define CPP_HSE_FILTER_SETTING_H

#include <string>
#include <vector>
class FilterSetting {

public:
    FilterSetting(){};

    explicit FilterSetting(std::string filter_name) : filter_name_(filter_name) {
    }

    FilterSetting(std::string filter_name, std::vector<std::string> parameters)
        : filter_name_(filter_name), parameters_(parameters) {
    }
    /// Filter name getter.
    const std::string& GetFilterName() const {
        return filter_name_;
    }
    /// Filter parameters setter
    void SetFilterParameters(std::vector<std::string> parameters) {
        parameters_ = parameters;
    }
    /// Filter parameters getters
    const std::vector<std::string> GetFilterParameters() const {
        return parameters_;
    }
    /// Get filter parameter at particular index
    const std::string& GetFilterParameter(uint8_t index) {
        return parameters_[index];
    };

private:
    std::string filter_name_;
    std::vector<std::string> parameters_;
};
#endif  // CPP_HSE_FILTER_SETTING_H
