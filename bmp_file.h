#pragma once

#include "image.h"
#include <filesystem>

class BMPFile {
public:
    struct Pixel {
        uint8_t blue, green, red;
    };

    struct BMPMagic {
        uint16_t format;
    };

    struct BMPHeader {
        uint32_t file_size;
        uint16_t specific1;
        uint16_t specific2;
        uint32_t offset;
    };

    struct BMPInfo {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t planes_num;
        uint16_t bits_per_pixel;
        uint32_t compression;
        int32_t raw_data_size;
        int32_t res_height;
        uint32_t res_width;
        uint32_t colors_num;
        uint32_t important_colors_num;
    };

public:
    explicit BMPFile(std::string_view path);

    void OpenImage(Image &image) const;

    void SaveImage(Image &image) const;

    static int32_t CalculatePadding(const BMPInfo &info);

    static uint32_t CalculateFileSize(const BMPInfo &info);

private:
    std::__fs::filesystem::path path_;
};
