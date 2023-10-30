//
// Created by vlad on 25.10.23.
//

#include "bmp_stream.h"

void BMPStream::OpenInputStream(const std::string& filename) {
    if (filename.empty()) {
        throw std::runtime_error("filename empty.");
    }
    if (file_.is_open()) {
        throw std::logic_error("file is already open.");
    }
    filename_ = filename;
    file_.open(filename_);
    if (!file_.is_open()) {
        throw std::logic_error("unknown error during OpenInputStream(filename).");
    }
}

void BMPStream::CloseInputStream() {
    if (!file_.is_open()) {
        throw std::logic_error("file is not already open.");
    }
    filename_.clear();
    file_.close();
    if (file_.is_open()) {
        throw std::logic_error("can't close file.");
    }
}

void BMPStream::ReadBMPFileHeader() {
    if (!file_.is_open()) {
        throw std::logic_error("file is not open.");
    }
    file_.seekg(0);
    file_.read(reinterpret_cast<char*>(&image_.GetFileHeader()), sizeof(BMPFileHeader));
    if (image_.GetFileHeader().signature != BMP_SIGNATURE) {
        throw std::runtime_error("wrong file type.");
    }
}

void BMPStream::ReadBMPDibHeader() {
    if (!file_.is_open()) {
        throw std::logic_error("file is not open.");
    }
    file_.read(reinterpret_cast<char*>(&image_.GetDibHeader()), sizeof(BMPDibHeader));
    if (image_.GetDibHeader().bit_per_pixel != BMP_BIT_PER_PIXEL) {
        throw std::runtime_error("wrong file bit per pixel resolution");
    }

    uint8_t padding = (4 - (image_.GetDibHeader().width * sizeof(Pixel)) % 4) % 4;

    image_.GetPixelArray().Initialize(image_.GetDibHeader().height, image_.GetDibHeader().width, padding);
}

void BMPStream::ReadPixelArray() {
    if (!file_.is_open()) {
        throw std::logic_error("file is not open.");
    }
    file_.read(reinterpret_cast<char*>(&image_.GetPixelArray().GetPixelMatrix()),
               image_.GetFileHeader().file_size - BMP_FILE_HEADER_SIZE - static_cast<uint32_t>(sizeof(BMPDibHeader)));
}

void BMPStream::ReadBMP() {
    ReadBMPFileHeader();
    ReadBMPDibHeader();
    ReadPixelArray();
}

void BMPStream::OpenOutputStream(const std::string& output_filename) {
    if (output_filename.empty()) {
        throw std::runtime_error("filename is empty.");
    }
    if (output_file_.is_open()) {
        throw std::logic_error("output file is already open.");
    }
    output_filename_ = output_filename;
    output_file_.open(output_filename_, std::ios::binary);
    if (!output_file_.is_open()) {
        throw std::runtime_error("unknown error in OpenOutputStream(filename).");
    }
}

void BMPStream::PrintBMPFileHeader() {
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    output_file_.seekp(0);
    output_file_.write(reinterpret_cast<char*>(&image_.GetFileHeader()), sizeof(BMPFileHeader));
}
void BMPStream::PrintBMPDibHeader() {
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    output_file_.write(reinterpret_cast<char*>(&image_.GetDibHeader()), sizeof(BMPDibHeader));
}
void BMPStream::PrintBMPPixelArray() {
    if (!output_file_.is_open()) {
        throw std::logic_error("output file is not already open.");
    }
    output_file_.write(reinterpret_cast<char*>(&image_.GetPixelArray().GetPixelMatrix()),
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
    if (!output_file_.is_open()) {
        throw std::logic_error("file is not already open.");
    }
    output_filename_.clear();
    output_file_.close();
    if (output_file_.is_open()) {
        throw std::runtime_error("unknown error in CloseOutputStream.");
    }
}
