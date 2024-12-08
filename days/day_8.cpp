#include "day_8.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <map>

std::tuple<std::tuple<int, int>, char> get_next_antenna(std::vector<std::string>& antenna_field, std::tuple<int, int>& current_pos) {
    int row = std::get<0>(current_pos);
    int col = std::get<1>(current_pos);
    if (row < 0
        || row >= antenna_field.size()
        || col < 0
        || col >= antenna_field.front().length()) throw std::runtime_error("Current position out of bounds!");
    for (;row < antenna_field.size();row++) {
        for (;col < antenna_field.front().length();col++) {
            if (isalnum(antenna_field[row][col])) return std::make_tuple(std::make_tuple(row, col), antenna_field[row][col]);
        }
    }
    return std::make_tuple(std::make_tuple(-1, -1), '0');
}
std::tuple<std::tuple<int, int>, char> get_next_antenna_of_type(std::vector<std::string>& antenna_field, std::tuple<int, int>& current_pos, char find_this) {
    int row = std::get<0>(current_pos);
    int col = std::get<1>(current_pos);
    if (row < 0
        || row >= antenna_field.size()
        || col < 0
        || col >= antenna_field.front().length()) throw std::runtime_error("Current position out of bounds!");
    for (;row < antenna_field.size();row++) {
        for (;col < antenna_field.front().length();col++) {
            if (isalnum(antenna_field[row][col])) {
                if (antenna_field[row][col] == find_this) return std::make_tuple(std::make_tuple(row, col), antenna_field[row][col]);
                else continue;
            }
        }
    }
    return std::make_tuple(std::make_tuple(-1, -1), '0');
}

std::tuple<std::tuple<int, int>, char> get_next_unique_antenna(std::vector<std::string>& antenna_field, std::tuple<int, int>& current_pos, std::set<char> known_symbols) {
    int row = std::get<0>(current_pos);
    int col = std::get<1>(current_pos);
    if (row < 0
        || row >= antenna_field.size()
        || col < 0
        || col >= antenna_field.front().length()) throw std::runtime_error("Current position out of bounds!");
    for (;row < antenna_field.size();row++) {
        for (;col < antenna_field.front().length();col++) {
            if (isalnum(antenna_field[row][col])) {
                if (known_symbols.count(antenna_field[row][col])) continue;
                else return std::make_tuple(std::make_tuple(row, col), antenna_field[row][col]);
            }
        }
    }
    return std::make_tuple(std::make_tuple(-1, -1), '0');
}

std::set<std::tuple<int, int>> get_antinodes(std::vector<std::string>& antenna_field, std::set<std::tuple<int, int>>& already_taken_coords, std::tuple<int, int> point_a, std::tuple<int, int> point_b) {
    std::set<std::tuple<int, int>> res = {};
    int maybe_rise = std::get<0>(point_b) * 2 - std::get<0>(point_a);
    int maybe_run = std::get<1>(point_b) * 2 - std::get<1>(point_a);
    if (maybe_rise < 0
        || maybe_rise >= antenna_field.size()
        || maybe_run < 0
        || maybe_run >= antenna_field.front().length()) {
    } else if (!already_taken_coords.count(std::make_tuple(maybe_rise, maybe_run))) {
        res.insert(std::make_tuple(maybe_rise, maybe_run));
    }
    maybe_rise = std::get<0>(point_a) * 2 - std::get<0>(point_b);
    maybe_run = std::get<1>(point_a) * 2 - std::get<1>(point_b);
    if (maybe_rise < 0
        || maybe_rise >= antenna_field.size()
        || maybe_run < 0
        || maybe_run >= antenna_field.front().length()) {
    } else if (!already_taken_coords.count(std::make_tuple(maybe_rise, maybe_run))) {
        res.insert(std::make_tuple(maybe_rise, maybe_run));
    }
    return res;
}
std::set<std::tuple<int, int>> get_antinodes_in_line(std::vector<std::string>& antenna_field, std::set<std::tuple<int, int>>& already_taken_coords, std::tuple<int, int> point_a, std::tuple<int, int> point_b) {
    std::set<std::tuple<int, int>> res = {};
    int rise = std::get<0>(point_b) - std::get<0>(point_a);
    int run = std::get<1>(point_b) - std::get<1>(point_a);
    int maybe_rise = std::get<0>(point_b) + rise;
    int maybe_run = std::get<1>(point_b) + run;
    while (maybe_rise >= 0
        && maybe_rise < antenna_field.size()
        && maybe_run >= 0
        && maybe_run < antenna_field.front().length()) {
        if (!already_taken_coords.count(std::make_tuple(maybe_rise, maybe_run))) {
            res.insert(std::make_tuple(maybe_rise, maybe_run));
        }
        maybe_rise += rise;
        maybe_run += run;
    }
    rise = std::get<0>(point_a) - std::get<0>(point_b);
    run = std::get<1>(point_a) - std::get<1>(point_b);
    maybe_rise = std::get<0>(point_a) + rise;
    maybe_run = std::get<1>(point_a) + run;
    while (maybe_rise >= 0
        && maybe_rise < antenna_field.size()
        && maybe_run >= 0
        && maybe_run < antenna_field.front().length()) {
        if (!already_taken_coords.count(std::make_tuple(maybe_rise, maybe_run))) {
            res.insert(std::make_tuple(maybe_rise, maybe_run));
        }
        maybe_rise += rise;
        maybe_run += run;
    }
    return res;
}



int part_1() {
    int how_many_antinodes = 0;
    std::vector<std::string> antenna_field = UTILS::get_input("input/day_8.txt");
    std::map<char, std::vector<std::tuple<int, int>>> symbol_coord_map = {};
    std::set<std::tuple<int, int>> already_taken_coords = {};
    for (int row = 0; row < antenna_field.size();row++) {
        for (int col = 0; col < antenna_field[row].length();col++) {
            if (symbol_coord_map.count(antenna_field[row][col])) {
                symbol_coord_map.at(antenna_field[row][col]).push_back(std::make_tuple(row, col));
                already_taken_coords.insert(std::make_tuple(row, col));
            } else if (isalnum(antenna_field[row][col])) {
                symbol_coord_map.insert({ antenna_field[row][col],{std::make_tuple(row, col)} });
                already_taken_coords.insert(std::make_tuple(row, col));
            }
        }
    }
    std::set<std::tuple<int, int>> known_antinodes = {};
    for (const auto& symbol_coords : symbol_coord_map) {
        char synbol = symbol_coords.first;
        std::vector<std::tuple<int, int>> coords = symbol_coords.second;
        for (int i = 0; i < coords.size() - 1; i++) {
            for (int j = i + 1; j < coords.size(); j++) {
                auto res = get_antinodes(antenna_field, known_antinodes, coords[i], coords[j]);
                for (auto single_cord : res) {
                    how_many_antinodes++;
                    known_antinodes.insert(single_cord);
                }
            }
        }
    }
    return how_many_antinodes;
}
int part_2() {
    std::vector<std::string> antenna_field = UTILS::get_input("input/day_8.txt");
    std::map<char, std::vector<std::tuple<int, int>>> symbol_coord_map = {};
    std::set<std::tuple<int, int>> already_taken_coords = {};
    for (int row = 0; row < antenna_field.size();row++) {
        for (int col = 0; col < antenna_field[row].length();col++) {
            if (symbol_coord_map.count(antenna_field[row][col])) {
                symbol_coord_map.at(antenna_field[row][col]).push_back(std::make_tuple(row, col));
                already_taken_coords.insert(std::make_tuple(row, col));
            } else if (isalnum(antenna_field[row][col])) {
                symbol_coord_map.insert({ antenna_field[row][col],{std::make_tuple(row, col)} });
                already_taken_coords.insert(std::make_tuple(row, col));
            }
        }
    }
    for (const auto& symbol_coords : symbol_coord_map) {
        char synbol = symbol_coords.first;
        std::vector<std::tuple<int, int>> coords = symbol_coords.second;
        for (int i = 0; i < coords.size() - 1; i++) {
            for (int j = i + 1; j < coords.size(); j++) {
                auto res = get_antinodes_in_line(antenna_field, already_taken_coords, coords[i], coords[j]);
                for (auto single_cord : res) {
                    already_taken_coords.insert(single_cord);
                }
            }
        }
    }
    return already_taken_coords.size();
}

void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}