//
// Created by vlad on 25.10.23.
//

#include "bmp_stream.h"

void BMPStream::OpenInputStream(const std::string& filename) {
    // check that input file path is not empty and input stream is not already open
    if (filename.empty()) {
        throw std::runtime_error("filename empty.");
    }
    if (file_.is_open()) {
        throw std::logic_error("file is already open.");
    }
    filename_ = filename;
    // open input stream and indicate about possible errors
    file_.open(filename_);
    if (!file_.is_open()) {
        throw std::logic_error("unknown error during OpenInputStream(filename).");
    }
}

void BMPStream::CloseInputStream() {
    // to close input stream it has to be already open
    if (!file_.is_open()) {
        throw std::logic_error("file is not already open.");
    }
    // clear input file values and indicate about possible errors
    filename_.clear();
    file_.close();
    if (file_.is_open()) {
        throw std::logic_error("can't close file.");
    }
}

void BMPStream::ReadBMPFileHeader() {
    // to read file header input stream has to be open
    if (!file_.is_open()) {
        throw std::logic_error("file is not open.");
    }
    // start reading from the first byte
    file_.seekg(0);
    file_.read(reinterpret_cast<char*>(&image_.GetFileHeader()), sizeof(BMPFileHeader));
    // check that we read BMP file
    if (image_.GetFileHeader().signature != BMP_SIGNATURE) {
        throw std::runtime_error("wrong file type.");
    }
}

void BMPStream::ReadBMPDibHeader() {
    // to read dib header input stream has to be open
    if (!file_.is_open()) {
        throw std::logic_error("file is not open.");
    }
    file_.read(reinterpret_cast<char*>(&image_.GetDibHeader()), sizeof(BMPDibHeader));
    // check that we work with particular bit resolution.
    if (image_.GetDibHeader().bit_per_pixel != BMP_BIT_PER_PIXEL) {
        throw std::runtime_error("wrong file bit per pixel resolution");
    }
    // calcukate new padding
    uint8_t padding = (4 - (image_.GetDibHeader().width * sizeof(Pixel)) % 4) % 4;
    // initialize new pixel storage
    image_.GetPixelArray().Initialize(image_.GetDibHeader().height, image_.GetDibHeader().width, padding);
}

void BMPStream::ReadPixelArray() {
    // to read pixels data input stream has to be open
    if (!file_.is_open()) {
        throw std::logic_error("file is not open.");
    }
    file_.read(reinterpret_cast<char*>(&image_.GetPixelArray().GetPixelMatrix()),  // read image size amount of bytes
               image_.GetFileHeader().file_size - BMP_FILE_HEADER_SIZE - static_cast<uint32_t>(sizeof(BMPDibHeader)));
}

void BMPStream::ReadBMP() {
    ReadBMPFileHeader();
    ReadBMPDibHeader();
    ReadPixelArray();
}

void BMPStream::OpenOutputStream(const std::string& output_filename) {
    // check that output file path is not empty and output stream is not already open
    if (output_filename.empty()) {
        throw std::runtime_error("filename is empty.");
    }
    if (output_file_.is_open()) {
        throw std::logic_error("output file is already open.");
    }
    output_filename_ = output_filename;
    // open input stream and indicate about possible errors
    output_file_.open(output_filename_, std::ios::binary);
    if (!output_file_.is_open()) {
        throw std::runtime_error("unknown error in OpenOutputStream(filename).");
    }
}

void BMPStream::PrintBMPFileHeader() {
    // to save file header output stream has to be open
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    // start reading from the first byte
    output_file_.seekp(0);
    output_file_.write(reinterpret_cast<char*>(&image_.GetFileHeader()), sizeof(BMPFileHeader));
}
void BMPStream::PrintBMPDibHeader() {
    // to save dib header output stream has to be open
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    output_file_.write(reinterpret_cast<char*>(&image_.GetDibHeader()), sizeof(BMPDibHeader));
}
void BMPStream::PrintBMPPixelArray() {
    // to save pixel storage output stream has to be empty
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    output_file_.write(
        reinterpret_cast<char*>(&image_.GetPixelArray().GetPixelMatrix()),  // save sizeof(pixel storage)  bytes
        image_.GetFileHeader().file_size - BMP_FILE_HEADER_SIZE - static_cast<uint32_t>(sizeof(BMPDibHeader)));
}
void BMPStream::PrintBMPImage() {
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    PrintBMPFileHeader();
    PrintBMPDibHeader();
    PrintBMPPixelArray();
}
void BMPStream::CloseOutputStream() {
    // to close output stream it has to be open
    if (!output_file_.is_open()) {
        throw std::logic_error("file is not already open.");
    }
    // clear output file values and indicate about possible errors
    output_filename_.clear();
    output_file_.close();
    if (output_file_.is_open()) {
        throw std::runtime_error("unknown error in CloseOutputStream.");
    }
}
