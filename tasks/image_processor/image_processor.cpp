#include <stdexcept>
#include <iostream>

#include "bmp_stream.h"
#include "clp.h"
#include "Filters/basic_filter.h"
#include "Filters/crop_filter.h"
#include "Filters/negative_filter.h"
#include "Filters/grayscale.h"
#include "Filters/sharping_filter.h"
#include "Filters/edge_detection.h"
#include "Filters/blur_filter.h"
#include "application.h"

const std::string TEST_FILE = "/home/vlad/final_project/tasks/image_processor/test_script/data/lenna.bmp";
const std::string OUTPUT_TEST_FILE = "../output_lenna.bmp";

int main(int argc, char* argv[]) {
    Application application(argc, argv);
    application.Execute();
    /*BMPStream bmp_stream;
    bmp_stream.OpenInputStream(TEST_FILE);
    bmp_stream.ReadBMP();
    bmp_stream.CloseInputStream();
    bmp_stream.OpenOutputStream(OUTPUT_TEST_FILE);
    bmp_stream.PrintBMPImage();
    bmp_stream.CloseOutputStream();*/
    return 0;
}
