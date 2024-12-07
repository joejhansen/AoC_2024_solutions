#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "day_2.h"
#include "utils.h"



bool is_safe(std::vector<int>input) {
    bool failed = false;
    int order = 0;
    for (int i = 0; i < input.size() - 1; i++) {
        int delta = input[i] - input[i + 1];
        if (order == 0) {
            if (delta < 0) {
                order = -1;
            } else if (delta > 0) {
                order = 1;
            }
        } else {
            if (order == -1 && delta >= 0) {
                failed = true;
                break;
            } else if (order == 1 && delta <= 0) {
                failed = true;
                break;
            }
        }
        delta = abs(delta);
        if (delta > 3 || delta < 1) {
            failed = true;
            break;
        }
    }
    return !failed;
}

int part_1() {
    std::vector<std::string> input = UTILS::get_input("input/day_2.txt");
    int safe_count = 0;
    for (std::string line : input) {
        if (is_safe(UTILS::split_string_to_ints(line, ' '))) {
            safe_count += 1;
        }
    }
    return safe_count;
}

int part_2() {
    std::vector<std::string> input = UTILS::get_input("input/day_2.txt");
    int safe_count = 0;
    for (std::string line : input) {
        std::vector<int> split_ints = UTILS::split_string_to_ints(line, ' ');
        if (is_safe(split_ints)) {
            safe_count += 1;
        } else {
            for (int i = 0; i < split_ints.size(); i++) {
                std::vector<int> tmp_ints(split_ints);
                tmp_ints.erase(tmp_ints.begin() + i);
                if (is_safe(tmp_ints)) {
                    safe_count += 1;
                    break;
                }
            }
        }
    }
    return safe_count;
}

void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}