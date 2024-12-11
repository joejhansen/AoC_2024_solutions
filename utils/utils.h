#include <vector>
#include <string>
#ifndef UTILS_H
#define UTILS

std::vector<std::string> get_input(std::string file_name);

std::vector<int> split_string_to_ints(std::string input, char delimiter);

std::vector<long> split_string_to_longs(std::string input, char delimiter);

std::vector<long long> split_string_to_long_longs(std::string input, char delimiter);

std::vector<unsigned long long> split_string_to_unsigned_long_longs(std::string input, char delimiter);

std::vector<std::string> split_string(std::string input, char delimiter);

#endif