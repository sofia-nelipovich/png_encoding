#pragma once

#include <string_view>
#include <vector>
#include <filesystem>

#include <memory>

namespace fs = std::__fs::filesystem;

struct CommandStruct {
    std::string_view name;
    std::vector<std::string_view> parameters;
};

class CLI {
public:
    CLI() = default;

    CLI(int args_number, char **args_vector);

    void ParseArgs(int args_number, char **args_vector);

    std::string_view GetInputFile() const;

    std::string_view GetOutputFile() const;

    bool IsParsed() const;

    std::vector<CommandStruct>& GetCommands();

private:


    std::string_view input_file_;
    std::string_view output_file_;
    std::vector<CommandStruct> commands_vector_;
    bool is_parsed_ = true;
};