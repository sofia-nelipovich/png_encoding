#include "image.h"
#include "bmp_file.h"
#include "cli.h"
#include <iostream>

int main(int argc, char **argv) {
    CLI cli;
    try {
        CLI cli_(argc, argv);
        cli = cli_;
    } catch (...) {
        std::cout << "Something gone wrong!\n";
        return 0;
    }

    Image image;
    BMPFile input_file(cli.GetInputFile());

    input_file.OpenImage(image);

    BMPFile output_file(cli.GetOutputFile());
    output_file.SaveImage(image);
    return 0;
}
