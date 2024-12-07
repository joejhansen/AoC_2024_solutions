#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "utils.h"

std::vector<std::string> get_input(std::string file_name) {
    std::vector<std::string> file_contents = {};
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

std::vector<int> split_string_to_ints(std::string input, char delimiter) {
    std::vector<int> res = {};
    std::string tmp = "";
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == delimiter) {
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

std::vector<std::string> split_string(std::string input, char delimiter) {
    std::vector<std::string> res = {};
    std::string tmp = "";
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == delimiter) {
            if (tmp != "") res.push_back(tmp);
            tmp = "";
        } else {
            tmp = tmp + input[i];
            if (i == input.length() - 1) {
                res.push_back(tmp);
            }
        }
    }
    return res;
}