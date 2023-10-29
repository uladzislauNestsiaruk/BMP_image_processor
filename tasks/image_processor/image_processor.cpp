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

int main(int argc, char* argv[]) {
    Application application(argc, argv);
    application.Execute();
    return 0;
}
