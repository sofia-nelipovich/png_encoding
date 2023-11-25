#include "bmp_file.h"

#include <fstream>
#include <stdexcept>
#include <limits>

static const uint16_t FORMAT = 0x4D42;
static const uint16_t BITS_PER_PIXEL = 24;
static const uint32_t OFFSET = sizeof(BMPFile::BMPMagic) + sizeof(BMPFile::BMPHeader) + sizeof(BMPFile::BMPInfo);

BMPFile::BMPFile(std::string_view path) : path_(path){};

void BMPFile::OpenImage(Image &image) const {

    auto &channels = image.GetChannels();
    BMPMagic format{};
    BMPHeader header{};
    BMPInfo info;

    std::ifstream file(path_, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw std::ios::failure("Couldn't open file:  " + path_.string());
    } else {

        file.read(reinterpret_cast<char *>(&format), sizeof(BMPMagic));
        file.read(reinterpret_cast<char *>(&header), sizeof(BMPHeader));
        file.read(reinterpret_cast<char *>(&info), sizeof(BMPInfo));

        if (format.format != FORMAT) {
            throw std::runtime_error("Not valid BMP format in " + path_.string());
        }
        if (info.planes_num != 1) {
            throw std::runtime_error("Planes number is wrong in " + path_.string());
        }
        if (info.bits_per_pixel != BITS_PER_PIXEL) {
            throw std::runtime_error("Pixel should be 24 bits in " + path_.string());
        }
        if (info.compression) {
            throw std::runtime_error("File " + path_.string() + " is compressed.");
        }
        if (info.colors_num || info.important_colors_num) {
            throw std::runtime_error("Colors table in " + path_.string());
        }
        if (info.width <= 0 || info.height == 0) {
            throw std::runtime_error("Bad BMP format in " + path_.string());
        }

        bool is_inverted = true;
        if (info.height < 0) {
            is_inverted = false;
            info.height = -info.height;
        }

        file.seekg(header.offset);

        Image::Channel blue_channel(info.height, std::vector<double>(info.width));
        Image::Channel green_channel(info.height, std::vector<double>(info.width));
        Image::Channel red_channel(info.height, std::vector<double>(info.width));

        for (int row = 0; row < info.height; ++row) {
            for (int column = 0; column < info.width; ++column) {
                int row_index = !is_inverted ? row : info.height - row - 1;
                blue_channel[row_index][column] = static_cast<double>(file.get()) / std::numeric_limits<uint8_t>::max();
                green_channel[row_index][column] =
                        static_cast<double>(file.get()) / std::numeric_limits<uint8_t>::max();
                red_channel[row_index][column] = static_cast<double>(file.get()) / std::numeric_limits<uint8_t>::max();
            }
            file.seekg(info.width % 4, std::ios::cur);
        }
        channels.push_back(blue_channel);
        channels.push_back(green_channel);
        channels.push_back(red_channel);
    }
}

void BMPFile::SaveImage(Image &image) const {
    auto &channels = image.GetChannels();
    std::ofstream file(path_, std::ios::binary);

    if (!file.is_open()) {
        throw std::ios::failure("Couldn't open file:  " + path_.string());
    }
    if (channels.empty() || channels.size() == 2) {
        std::runtime_error("Something went wrong!");
    }

    BMPMagic format = {FORMAT};

    BMPHeader header = {0, 0, 0, OFFSET};
    BMPInfo info = {sizeof(BMPInfo), 0, 0, 1, BITS_PER_PIXEL, 0, 0, 0, 0, 0, 0};

    file.write(reinterpret_cast<char *>(&format), sizeof(format));

    info.height = static_cast<int32_t>(channels[0].size());
    info.width = static_cast<int32_t>(channels[0][0].size());

    if (info.height == 0 || info.width == 0) {
        std::runtime_error("Something went wrong!");
    }

    header.file_size = CalculateFileSize(info);

    file.write(reinterpret_cast<const char *>(&header), sizeof(header));
    file.write(reinterpret_cast<const char *>(&info), sizeof(info));

    for (int32_t row = info.height - 1; row >= 0; --row) {
        for (int32_t column = 0; column < info.width; ++column) {
            size_t green_ind = channels.size() == 1 ? 0 : 1;
            size_t red_ind = channels.size() == 1 ? 0 : 2;
            Pixel pixel = {static_cast<uint8_t>(channels[0][row][column] *
                                                static_cast<double>(std::numeric_limits<uint8_t>::max())),
                           static_cast<uint8_t>(channels[green_ind][row][column] *
                                                static_cast<double>(std::numeric_limits<uint8_t>::max())),
                           static_cast<uint8_t>(channels[red_ind][row][column] *
                                                static_cast<double>(std::numeric_limits<uint8_t>::max()))};

            file.write(reinterpret_cast<const char *>(&pixel), sizeof(pixel));
        }
        for (int pad = 0; pad < CalculatePadding(info); ++pad) {
            file.put(0);
        }
    }
}

int32_t BMPFile::CalculatePadding(const BMPInfo &info) {
    return info.width % 4;
}

uint32_t BMPFile::CalculateFileSize(const BMPInfo &info) {
    return OFFSET + info.width * info.height * 3 + CalculatePadding(info) * info.height;
}
