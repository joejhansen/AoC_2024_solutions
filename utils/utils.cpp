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