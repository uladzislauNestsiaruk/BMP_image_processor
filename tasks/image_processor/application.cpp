//
// Created by vlad on 29.10.23.
//

#include "application.h"
#include "bmp_stream.h"
#include "filter_factory .h"
#include "clp.h"

Application::Application(int argc, char **argv) {
    argc_ = argc;
    argv_ = new char*[argc_];
    for(int index = 0; index < argc_; ++index){
        argv_[index] = argv[index];
    }
}
void Application::Execute() {
    CLP clp;
    std::string input_file;
    std::string output_file;
    std::vector<FilterSetting> filters_settings = clp.ParametersToFilterSetting(argc_, argv_,
                                                                                input_file, output_file);
    BMPStream bmp_stream;
    bmp_stream.OpenInputStream(input_file);
    bmp_stream.ReadBMP();
    bmp_stream.CloseInputStream();
    FilterFactory filters_factory(filters_settings);
    Pipeline pipeline = filters_factory.BuildPipeline();
    pipeline.ApplyFilters(bmp_stream);

    bmp_stream.OpenOutputStream(output_file);
    bmp_stream.PrintBMPImage();
    bmp_stream.CloseOutputStream();
}
