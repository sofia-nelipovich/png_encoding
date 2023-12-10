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

struct PNGDecoderParameters {
    uint32_t LZ77_window_size;
    uint32_t LZ77_match_length = 0;
    Block block;
};

class PNGImage {
public:
    inline bool ConvertToPNGFromBMP(std::vector<unsigned char>& image, Image& bmp) {
        using Channel = std::vector<std::vector<double>>;
        std::vector<Channel> &channels_ = bmp.GetChannels();
        return false;
    }
private:
    size_t width_;
    size_t height_;
    size_t size_;
};