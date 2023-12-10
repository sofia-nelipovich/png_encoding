#pragma once

#include <string>
#include <vector>

class Image {
public:
    using Channel = std::vector<std::vector<double>>;

    Image() = default;

    inline Image(int width, int height);

    ~Image() = default;

    inline double GetColorR(int x, int y) const;

    inline double GetColorG(int x, int y) const;

    inline double GetColorB(int x, int y) const;

    inline void SetColorR(double value, int x, int y);

    inline void SetColorG(double value, int x, int y);

    inline void SetColorB(double value, int x, int y);

    inline size_t GetWidth() const;

    inline size_t GetHeight() const;

    std::vector<Channel> &GetChannels();

    inline void ChangeSize();

private:
    std::vector<Channel> channels_;
    int width_;
    int height_;
};

inline std::vector<Image::Channel> &Image::GetChannels() {
    return channels_;
}

void Image::ChangeSize() {
    for (size_t i = 0; i < channels_.size(); ++i) {
        channels_[i].resize(width_);
        for (size_t j = 0; j < channels_[i].size(); ++j) {
            channels_[i][j].clear();
            channels_[i][j].resize(height_);
        }
    }
}

Image::Image(int width, int height) : width_(width), height_(height) {
    for (size_t i = 0; i < 3; ++i) {
        Channel channel;
        channel.resize(width, std::vector<double>(height, 0));
        channels_.push_back(channel);
    }
}

double Image::GetColorR(int x, int y) const {
    return channels_[0][x][y];
}

double Image::GetColorG(int x, int y) const {
    if (channels_.size() == 3) {
        return channels_[1][x][y];
    } else {
        return channels_[0][x][y];
    }
}

double Image::GetColorB(int x, int y) const {
    if (channels_.size() == 3) {
        return channels_[2][x][y];
    } else {
        return channels_[0][x][y];
    }
}

void Image::SetColorR(double value, int x, int y) {
    channels_[0][x][y] = value;
}
void Image::SetColorG(double value, int x, int y) {
    channels_[1][x][y] = value;
}
void Image::SetColorB(double value, int x, int y) {
    channels_[2][x][y] = value;
}

size_t Image::GetWidth() const {
    return channels_[0].size();
}

size_t Image::GetHeight() const {
    return channels_[0][0].size();
}
