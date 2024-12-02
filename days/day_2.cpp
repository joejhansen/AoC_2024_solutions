#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "day_2.h"

std::vector<std::string> get_input() {
    std::vector<std::string> file_contents = {};
    std::string file_name = "input/day_2.txt";
    std::ifstream file(file_name);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            file_contents.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << file_name << std::endl;
    }
    return file_contents;
}

std::vector<int> split_line(std::string input, char deliminator) {
    std::vector<int> res = {};
    std::string tmp = "";
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == deliminator) {
            res.push_back(stoi(tmp));
            tmp = "";
        } else {
            tmp = tmp + input[i];
            if (i == input.length() - 1) {
                res.push_back(stoi(tmp));
            }
        }
    }
    return res;
}

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
    std::vector<std::string> input = get_input();
    int safe_count = 0;
    for (std::string line : input) {
        if (is_safe(split_line(line, ' '))) {
            safe_count += 1;
        }
    }
    return safe_count;
}

int part_2() {
    std::vector<std::string> input = get_input();
    int safe_count = 0;
    for (std::string line : input) {
        std::vector<int> split_ints = split_line(line, ' ');
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