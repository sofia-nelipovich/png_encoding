#pragma once

#include <iostream>
#include "image.h"
#ifndef PNG_ENCODING_PNG_ENCODE_H
#define PNG_ENCODING_PNG_ENCODE_H

#endif //PNG_ENCODING_PNG_ENCODE_H

struct Block {
    int32_t offset;
    int32_t length;
    int32_t next;
};

struct PNGEncoderParameters {
    uint32_t LZ77_window_size = 128;
    uint32_t LZ77_match_length = 0;
    Block block;
};

class PNGImage {
public:
    PNGImage(size_t width, size_t height);

    PNGImage() = default;

    ~PNGImage() = default;

    static inline bool ConvertToPNGFromBMP(Image& bmp);
private:
    size_t width_ = 0;
    size_t height_ = 0;
    size_t size_ = 0;
    std::vector<unsigned char> image_;
};