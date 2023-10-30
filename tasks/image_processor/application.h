//
// Created by vlad on 29.10.23.
//

#ifndef CPP_HSE_APPLICATION_H
#define CPP_HSE_APPLICATION_H

#include <stdexcept>
#include "bmp_stream.h"

class Application {

public:
    Application(int argc, char* argv[]);
    /// Open input stream and return true if no exceptions were found
    bool OpenInputStreamExceptionHandler(BMPStream& bmp_stream, const std::string& input_file);
    // Close input stream and return true if no exceptions were found
    bool OpenOutputStreamExceptionHandler(BMPStream& bmp_stream, const std::string& output_file);
    // Read bmp file and return true if no exceptions were found
    bool ReadBMPExceptionHandler(BMPStream& bmp_stream);
    // Save bmp file and return true if no exceptions were found
    bool PrintBMPExceptionHandler(BMPStream& bmp_stream);
    /// Close input stream and return true if no exceptions were found
    bool CloseInputStreamExceptionHandler(BMPStream& bmp_stream);
    // Close output stream and return true if no exceptions were found
    bool CloseOutputStreamExceptionHandler(BMPStream& bmp_stream);
    // Trying to open read and close input file, return true if no exceptions were found
    bool WorkWithInputStream(BMPStream& bmp_stream, const std::string& input_file);
    // Trying to open sve into and close output file, return true if no exceptions were found
    bool WorkWithOutputStream(BMPStream& bmp_stream, const std::string& output_file);

    void Execute();

    ~Application();

private:
    int argc_;
    char** argv_;
};

#endif  // CPP_HSE_APPLICATION_H
