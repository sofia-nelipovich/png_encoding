
#include "png_encode.h"

PNGImage::PNGImage(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    image_.resize(width * height * 4);
}

bool PNGImage::ConvertToPNGFromBMP(Image &bmp) {
    using Channel = std::vector<std::vector<double>>;
    std::vector<Channel> &channels_ = bmp.GetChannels();
    return false;
}

