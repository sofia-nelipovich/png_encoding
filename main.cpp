#include "image.h"
#include "bmp_file.h"
#include "cli.h"
#include "commands.h"
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
    for (auto& command : cli.GetCommands()) {
        if (command.name == "-crop") {
            if (command.parameters.size() != 2) {
                std::cout << "You need to enter both width and height to crop an image." << std::endl;
            } else {
                int width = std::stoi(std::string(command.parameters[0]));
                int height = std::stoi(std::string(command.parameters[1]));
                CropCommand crop;
                crop.ApplyCommand(width, height, image);
            }
        }

    }
    BMPFile output_file(cli.GetOutputFile());
    output_file.SaveImage(image);
    return 0;
}
