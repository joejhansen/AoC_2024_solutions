#include "day_10.h"
#include "utils.h"
#include <iostream>
#include <set>
#include <tuple>

void get_end_positions_from(std::vector<std::string>& input_field, std::set<std::tuple<int, int>>& known_endpoints, std::tuple<int, int> from_position) {
    char curr_height = input_field[std::get<0>(from_position)][std::get<1>(from_position)];
    int rise;
    int run;
    for (int i = 0; i < 4;i++) {
        switch (i) {
            case 0:
                rise = 1, run = 0;
                break;
            case 1:
                rise = 0, run = 1;
                break;
            case 2:
                rise = -1, run = 0;
                break;
            case 3:
                rise = 0, run = -1;
                break;
            default:
                break;
        }
        if (std::get<0>(from_position) + rise < 0
            || std::get<0>(from_position) + rise >= input_field.size()
            || std::get<1>(from_position) + run < 0
            || std::get<1>(from_position) + run >= input_field.front().length()) {
            continue;
        }
        char next = input_field[std::get<0>(from_position) + rise][std::get<1>(from_position) + run];
        if (next - curr_height == 1) {
            if (next == '9') {
                known_endpoints.insert(std::make_tuple(std::get<0>(from_position) + rise, std::get<1>(from_position) + run));
            } else {
                get_end_positions_from(input_field, known_endpoints, std::make_tuple(std::get<0>(from_position) + rise, std::get<1>(from_position) + run));
            }
        }
    }
}

int part_1() {
    std::vector<std::string> input_field = UTILS::get_input("input/day_10.txt");
    int res = 0;
    for (int row = 0; row < input_field.size(); row++) {
        for (int col = 0; col < input_field.front().length(); col++) {
            if (input_field[row][col] == '0') {
                std::set<std::tuple<int, int>> known_endpoints = {};
                get_end_positions_from(input_field, known_endpoints, std::make_tuple(row, col));
                res += known_endpoints.size();
            }
        }
    }
    return res;
}

void get_trail_paths_from(std::vector<std::string>& input_field, std::vector<std::tuple<int, int>>& known_endpoints, std::tuple<int, int> from_position) { // all i did was change it from a set to a vector lol
    char curr_height = input_field[std::get<0>(from_position)][std::get<1>(from_position)];
    int rise;
    int run;
    for (int i = 0; i < 4;i++) {
        switch (i) {
            case 0:
                rise = 1, run = 0;
                break;
            case 1:
                rise = 0, run = 1;
                break;
            case 2:
                rise = -1, run = 0;
                break;
            case 3:
                rise = 0, run = -1;
                break;
            default:
                break;
        }
        if (std::get<0>(from_position) + rise < 0
            || std::get<0>(from_position) + rise >= input_field.size()
            || std::get<1>(from_position) + run < 0
            || std::get<1>(from_position) + run >= input_field.front().length()) {
            continue;
        }
        char next = input_field[std::get<0>(from_position) + rise][std::get<1>(from_position) + run];
        if (next - curr_height == 1) {
            if (next == '9') {
                known_endpoints.push_back(std::make_tuple(std::get<0>(from_position) + rise, std::get<1>(from_position) + run));
            } else {
                get_trail_paths_from(input_field, known_endpoints, std::make_tuple(std::get<0>(from_position) + rise, std::get<1>(from_position) + run));
            }
        }
    }
}

int part_2() {
    std::vector<std::string> input_field = UTILS::get_input("input/day_10.txt");
    int res = 0;
    for (int row = 0; row < input_field.size(); row++) {
        for (int col = 0; col < input_field.front().length(); col++) {
            if (input_field[row][col] == '0') {
                std::vector<std::tuple<int, int>> known_endpoints = {};
                get_trail_paths_from(input_field, known_endpoints, std::make_tuple(row, col));
                res += known_endpoints.size();
            }
        }
    }
    return res;
}

void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}