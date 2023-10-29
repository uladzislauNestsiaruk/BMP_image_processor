//
// Created by vlad on 25.10.23.
//

#include "bmp_stream.h"

void BMPStream::OpenInputStream(const std::string &filename) {
    if(filename.empty()){
        throw std::runtime_error("filename empty.");
    }
    if(file_.is_open()){
        throw std::logic_error("file is already open.");
    }
    filename_ = filename;
    file_.open(filename_);
    if(!file_.is_open()){
        throw std::logic_error("unknown error during OpenInputStream(filename).");
    }
}

void BMPStream::CloseInputStream() {
    if(!file_.is_open()){
        throw std::logic_error("file is not already open.");
    }
    filename_.clear();
    file_.close();
    if(file_.is_open()){
        throw std::logic_error("can't close file.");
    }
}

void BMPStream::ReadBMPFileHeader() {
    if(!file_.is_open()){
        throw std::logic_error("file is not open.");
    }
    file_.seekg(0);
    file_.read(reinterpret_cast<char*>(&file_header_), sizeof(BMPFileHeader));
    if(file_header_.signature != BMP_SIGNATURE){
        throw std::runtime_error("wrong file type.");
    }
}

void BMPStream::ReadBMPDibHeader() {
    if(!file_.is_open()){
        throw std::logic_error("file is not open.");
    }
    file_.read(reinterpret_cast<char*>(&dib_header_), sizeof(BMPDibHeader));
    if(dib_header_.bit_per_pixel != BMP_BIT_PER_PIXEL){
        throw std::runtime_error("wrong file bit per pixel resolution");
    }

    uint8_t padding = (4 - (dib_header_.width * sizeof(Pixel))% 4) % 4;

    pixel_array_.Initialize(dib_header_.height, dib_header_.width, padding);
}

void BMPStream::ReadPixelArray() {
    if(!file_.is_open()){
        throw std::logic_error("file is not open.");
    }
    file_.read(reinterpret_cast<char*>(&pixel_array_.GetPixelMatrix()),
               file_header_.file_size - BMP_FILE_HEADER_SIZE - dib_header_.size);
}

void BMPStream::ReadBMP() {
    ReadBMPFileHeader();
    ReadBMPDibHeader();
    ReadPixelArray();
}

void BMPStream::OpenOutputStream(const std::string& output_filename) {
    if(output_filename.empty()){
        throw std::runtime_error("filename is empty.");
    }
    if(output_file_.is_open()){
        throw std::logic_error("output file is already open.");
    }
    output_filename_ = output_filename;
    output_file_.open(output_filename_);
    if(!output_file_.is_open()){
        throw std::runtime_error("unknown error in OpenOutputStream(filename).");
    }
}

void BMPStream::PrintBMPFileHeader() {
    if(!output_file_.is_open()){
        throw std::logic_error("output file is not already open.");
    }
    output_file_.seekp(0);
    output_file_.write(reinterpret_cast<char*>(&file_header_), sizeof(BMPFileHeader));
}
void BMPStream::PrintBMPDibHeader() {
    if(!output_file_.is_open()){
        throw std::logic_error("output file is not already open.");
    }
    output_file_.write(reinterpret_cast<char*>(&dib_header_), sizeof(BMPDibHeader));
}
void BMPStream::PrintBMPPixelArray() {
    if(!output_file_.is_open()){
        throw std::logic_error("output file is not already open.");
    }
    output_file_.write(reinterpret_cast<char*>(&pixel_array_.GetPixelMatrix()), file_header_.file_size - BMP_FILE_HEADER_SIZE - dib_header_.size);
}
void BMPStream::PrintBMPImage() {
    if(!output_file_.is_open()){
        throw std::logic_error("output file is not already open.");
    }
    PrintBMPFileHeader();
    PrintBMPDibHeader();
    PrintBMPPixelArray();
}
void BMPStream::CloseOutputStream() {
    if(!output_file_.is_open()){
        throw std::logic_error("file is not already open.");
    }
    output_filename_.clear();
    output_file_.close();
    if(output_file_.is_open()){
        throw std::runtime_error("unknown error in CloseOutputStream.");
    }
}
void BMPStream::UpdatePixelArraySizeDescription(uint32_t new_image_size) {
    dib_header_.image_size = 0;
    file_header_.file_size = BMP_FILE_HEADER_SIZE + dib_header_.size + new_image_size;
}
