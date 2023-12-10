#ifndef PNG_ENCODING_COMMANDS_H
#define PNG_ENCODING_COMMANDS_H

#endif //PNG_ENCODING_COMMANDS_H

#pragma once
#include "image.h"
#include <iostream>

class Command {
public:
    virtual void ApplyCommand(Image &image) const = 0;
    virtual ~Command() = default;
};

class CropCommand {
public:
    CropCommand() = default;
    using Channel = std::vector<std::vector<double>>;
    ~CropCommand() = default;
    void ApplyCommand(int width, int height, Image &image) const {
        std::vector<Channel>& image_channels = image.GetChannels();
        if (width > image.GetWidth() && height > image.GetHeight()) {
            return;
        }

        for (size_t i = 0; i < image_channels.size(); ++i) {
            image_channels[i].resize(width);
            for (size_t x = 0; x < width; ++x) {
                image_channels[i][x].resize(height);
            }
        }
    }
};
