#include <string>
#include <tuple>
#include <vector>
#ifndef DAY_1_H
#define DAY_1

std::vector<std::string> get_input();

std::tuple<std::vector<int>, std::vector<int>> get_sorted_lists( std::vector<std::string> input);

std::tuple<int, int> get_pair(std::string input);

int day_1_part_1();

int day_1_part_2();

#endif