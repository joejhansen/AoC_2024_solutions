#include <iostream>
#include <map>
#include <regex>
#include "day_3.h"
#include "utils.h"

int mul_from_str(std::string mul_str) {
    std::string tmp_str = mul_str.substr(4, mul_str.length() - 5); // we assume it starts with mul( and ends with )
    std::string num_1 = "";
    std::string num_2 = "";
    bool first = true;
    for (char c : tmp_str) {
        if (!isdigit(c)) {
            first = false;
        } else if (first) {
            num_1 = num_1 + c;
        } else {
            num_2 = num_2 + c;
        }
    }
    return std::stoi(num_1) * std::stoi(num_2);
}

int part_1() {
    std::regex regex("mul\\([0-9]+,[0-9]+\\)");
    std::vector<std::string> input = UTILS::get_input("input/day_3.txt");
    int res = 0;
    for (std::string line : input) {
        std::smatch matches;
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), matches, regex)) {
            res += mul_from_str(matches[0]);
            searchStart = matches.suffix().first;
        }
    }
    return res;
}
int part_2() {
    std::regex regex("mul\\([0-9]+,[0-9]+\\)|don't\\(\\)|do\\(\\)");
    std::vector<std::string> input = UTILS::get_input("input/day_3.txt");
    int res = 0;
    bool enabled = true;
    for (std::string line : input) {
        std::smatch matches;
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), matches, regex)) {
            if (matches[0] == "don't()") {
                enabled = false;
            } else if (matches[0] == "do()") {
                enabled = true;
            } else if (enabled) {
                res += mul_from_str(matches[0]);
            }
            searchStart = matches.suffix().first;
        }
    }
    return res;
}

void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}