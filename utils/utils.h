#include <vector>
#include <string>
#ifndef UTILS_H
#define UTILS

std::vector<std::string> get_input(std::string file_name);

std::vector<int> split_string_to_ints(std::string input, char delimiter);

std::vector<std::string> split_string(std::string input, char delimiter);

#endif