//
// Created by vlad on 29.10.23.
//

#include <iostream>
#include "application.h"
#include "bmp_stream.h"
#include "filter_factory.h"
#include "clp.h"

Application::Application(int argc, char **argv) {
    argc_ = argc;
    argv_ = new char *[argc_];
    for (int index = 0; index < argc_; ++index) {
        argv_[index] = argv[index];
    }
}

Application::~Application() {
    delete[] argv_;
}

void Application::Execute() {
    // Parse command line arguments
    CLP clp;
    std::string input_file;
    std::string output_file;
    std::vector<FilterSetting> filters_settings;
    try {
        filters_settings = clp.ParametersToFilterSetting(argc_, argv_, input_file, output_file);
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        return;
    } catch (...) {
        std::cerr << "Unknown error.\n";
        return;
    }
    // Read bmp from input
    BMP bmp;
    BMPStream bmp_stream(bmp);
    bmp_stream.OpenInputStream(input_file);
    bmp_stream.ReadBMP();
    bmp_stream.CloseInputStream();
    // Apply all filters to the image
    FilterFactory filters_factory(filters_settings);
    Pipeline pipeline = filters_factory.BuildPipeline();
    pipeline.ApplyFilters(bmp);
    // Print final image
    bmp_stream.OpenOutputStream(output_file);
    bmp_stream.PrintBMPImage();
    bmp_stream.CloseOutputStream();
}
