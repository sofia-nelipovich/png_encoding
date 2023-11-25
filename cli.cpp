#include "cli.h"

#include <stdexcept>
#include <iostream>

static const size_t INPUT_FILE_INDEX = 1;
static const size_t OUTPUT_FILE_INDEX = 2;

namespace {
    void PrintHelp() {
        std::cout << "This is a simple png encoding script.\n";
        std::cout << "-------------------------------------------------------------\n";
        std::cout << "How to input arguments:\n";
        std::cout << "\t./png_encoding input_file output_file -s n\n";
        std::cout << "-------------------------------------------------------------\n";
        std::cout
                << "-s parameter is not necessarily, n should be greater than 0, "
                   "if you added -s 10, it means you will get the same picture 10 times smaller.\n";
    }
}  // namespace

CLI::CLI(int args_number, char **args_vector) {
    ParseArgs(args_number, args_vector);
}

void CLI::ParseArgs(int args_number, char **args_vector) {
    if (args_number == 1) {
        // 1 argument - executable program
        is_parsed_ = false;
        PrintHelp();
    } else if (args_number == 2) {
        // 2 arguments - executable program + input file
        is_parsed_ = false;
        throw std::runtime_error("Not enough arguments!");
    } else if (args_number == 3) {
        // 3 arguments - executable program + input & output file, meaning we can save image in output file
        input_file_ = std::string_view(args_vector[INPUT_FILE_INDEX]);
        output_file_ = std::string_view(args_vector[OUTPUT_FILE_INDEX]);
    } else {
        // 4 arguments - executable program + input & output file + -s n
        input_file_ = std::string_view(args_vector[INPUT_FILE_INDEX]);
        output_file_ = std::string_view(args_vector[OUTPUT_FILE_INDEX]);
        if (args_vector[3][0] == '-') {
            FilterStruct new_filter;
            new_filter.name = args_vector[3];
//            filters_vector_.push_back(new_filter);
        } else {
            throw std::invalid_argument("Wrong argument: " + std::string(args_vector[3]));
//            filters_vector_[filters_vector_.size() - 1].parameters.push_back(args_vector[3]);
        }

    }
}

std::string_view CLI::GetInputFile() const {
    return input_file_;
}

std::string_view CLI::GetOutputFile() const {
    return output_file_;
}

bool CLI::IsParsed() const {
    return is_parsed_;
}
