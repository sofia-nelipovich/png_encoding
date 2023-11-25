cmake_minimum_required(VERSION 3.22)
project(png_encoding)

set(CMAKE_CXX_STANDARD 14)

add_executable(png_encoding
        main.cpp
        cli.cpp cli.h
        bmp_file.cpp bmp_file.h
        image.h
        )
