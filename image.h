#pragma once

#include <string>
#include <vector>

class Image {
public:
    using Channel = std::vector<std::vector<double>>;

    Image() = default;

    ~Image() = default;

    std::vector<Channel> &GetChannels();

private:
    std::vector<Channel> channels_;
};

std::vector<Image::Channel> &Image::GetChannels() {
    return channels_;
}
