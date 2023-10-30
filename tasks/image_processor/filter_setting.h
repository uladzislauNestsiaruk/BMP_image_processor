//
// Created by vlad on 26.10.23.
//

#ifndef CPP_HSE_FILTER_SETTING_H
#define CPP_HSE_FILTER_SETTING_H

#include <string>
class FilterSetting {

public:
    FilterSetting(){};

    explicit FilterSetting(std::string filter_name) : filter_name_(filter_name) {
    }

    const std::string& GetFilterName() const {
        return filter_name_;
    }

    const uint8_t GetFilterParametersAmount() const {
        return parameters_amount_;
    }

    const std::string* GetFilterParameters() const {
        return parameters_;
    }

    const std::string& GetFilterParameter(uint8_t index) {
        return parameters_[index];
    };

    void SetParameters(std::string* parameters, uint8_t parameters_amount) {
        parameters_amount_ = parameters_amount, parameters_ = parameters;
    }

    ~FilterSetting();

private:
    std::string filter_name_;
    std::string* parameters_;
    uint8_t parameters_amount_;
};
FilterSetting::~FilterSetting() {
    if (parameters_amount_ > 0) {
        delete[] parameters_;
    } else {
        delete parameters_;
    }
}
#endif  // CPP_HSE_FILTER_SETTING_H
