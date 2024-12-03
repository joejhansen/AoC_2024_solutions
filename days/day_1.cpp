#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "day_1.h"
#include "utils.h"

std::tuple<int, int> get_pair(std::string input) {
    std::string val1;
    std::string val2;
    bool first = true;
    for (char ch : input) {
        if (ch == ' ') {
            first = false;
            continue;
        }
        if (first) {
            val1 = val1 + ch;
        } else {
            val2 = val2 + ch;
        }
    }
    return std::make_tuple(stoi(val1), stoi(val2));
}

std::tuple<std::vector<int>, std::vector<int>> get_sorted_lists(std::vector<std::string> input) {
    std::vector<int> list_L = {};
    std::vector<int> list_R = {};
    for (std::string line : input) {
        std::tuple<int, int> int_pair = get_pair(line);
        list_L.push_back(std::get<0>(int_pair));
        list_R.push_back(std::get<1>(int_pair));
    }
    sort(list_L.begin(), list_L.end());
    sort(list_R.begin(), list_R.end());
    return std::make_tuple(list_L, list_R);
}

int part_1() {
    std::vector<std::string> pairs = UTILS::get_input("input/day_1.txt");
    std::tuple<std::vector<int>, std::vector<int>> sorted_lists = get_sorted_lists(pairs);
    int distance = 0;
    for (int i = 0; i < std::get<0>(sorted_lists).size(); i++) {
        distance += abs(std::get<0>(sorted_lists)[i] - std::get<1>(sorted_lists)[i]);
    }
    return distance;
}

int part_2() {
    std::tuple<std::vector<int>, std::vector<int>> sorted_lists = get_sorted_lists(UTILS::get_input("input/day_1.txt"));
    std::map<int, int> occ_map = {};
    int result = 0;
    for (int left_val : std::get<0>(sorted_lists)) {
        if (occ_map.count(left_val)) {
            result += left_val * occ_map.at(left_val);
        } else {
            occ_map.insert({ left_val, std::count(std::get<1>(sorted_lists).begin(), std::get<1>(sorted_lists).end(), left_val) });
            result += left_val * occ_map.at(left_val);
        }
    }
    return result;
}

void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}