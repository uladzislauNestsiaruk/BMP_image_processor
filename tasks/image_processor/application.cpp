//
// Created by vlad on 29.10.23.
//

#include <iostream>
#include "application.h"
#include "bmp_stream.h"
#include "filter_factory.h"
#include "clp.h"

Application::Application(int argc, char** argv) {
    argc_ = argc;
    argv_ = new char*[argc_];
    for (int index = 0; index < argc_; ++index) {
        argv_[index] = argv[index];
    }
}

Application::~Application() {
    delete[] argv_;
}

bool Application::OpenInputStreamExceptionHandler(BMPStream& bmp_stream, const std::string& input_file) {
    try {
        bmp_stream.OpenInputStream(input_file);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file reading.\n";
        return false;
    }
    return true;
}

bool Application::OpenOutputStreamExceptionHandler(BMPStream& bmp_stream, const std::string& output_file) {
    try {
        bmp_stream.OpenOutputStream(output_file);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file saving.\n";
        return false;
    }
    return true;
}

bool Application::ReadBMPExceptionHandler(BMPStream& bmp_stream) {
    try {
        bmp_stream.ReadBMP();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file reading.\n";
        return false;
    }
    return true;
}

bool Application::PrintBMPExceptionHandler(BMPStream& bmp_stream) {
    try {
        bmp_stream.PrintBMPImage();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file saving.\n";
        return false;
    }
    return true;
}

bool Application::CloseInputStreamExceptionHandler(BMPStream& bmp_stream) {
    try {
        bmp_stream.CloseInputStream();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file reading.\n";
        return false;
    }
    return true;
}

bool Application::CloseOutputStreamExceptionHandler(BMPStream& bmp_stream) {
    try {
        bmp_stream.CloseOutputStream();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file saving.\n";
        return false;
    }
    return true;
}

bool Application::WorkWithInputStream(BMPStream& bmp_stream, const std::string& input_file) {
    try {
        return OpenInputStreamExceptionHandler(bmp_stream, input_file) && ReadBMPExceptionHandler(bmp_stream) &&
               CloseInputStreamExceptionHandler(bmp_stream);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file reading.\n";
        return false;
    }
}

bool Application::WorkWithOutputStream(BMPStream& bmp_stream, const std::string& output_file) {
    try {
        return OpenOutputStreamExceptionHandler(bmp_stream, output_file) && PrintBMPExceptionHandler(bmp_stream) &&
               CloseOutputStreamExceptionHandler(bmp_stream);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return false;
    } catch (...) {
        std::cerr << "Unknown error during file reading.\n";
        return false;
    }
}

void Application::Execute() {
    // Parse command line arguments
    CLP clp;
    std::string input_file;
    std::string output_file;
    std::vector<FilterSetting> filters_settings;
    try {
        filters_settings = clp.ParametersToFilterSetting(argc_, argv_, input_file, output_file);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return;
    } catch (...) {
        std::cerr << "Unknown error.\n";
        return;
    }
    // Read bmp from input
    BMP bmp;
    BMPStream bmp_stream(bmp);
    if (!WorkWithInputStream(bmp_stream, input_file)) {
        return;
    }
    // Apply all filters to the image
    FilterFactory filters_factory(filters_settings);
    Pipeline pipeline = filters_factory.BuildPipeline();
    pipeline.ApplyFilters(bmp);
    // Print final image
    WorkWithOutputStream(bmp_stream, output_file);
}