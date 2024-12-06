#include "day_6.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>
#include <set>
#include <map>
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
int count_in_2d_vec(std::vector<std::string>& vec_2d, char find_me) {
    int res = 0;
    for (std::string line : vec_2d) {
        for (char ch : line) {
            if (ch == find_me) {
                res += 1;
            }
        }
    }
    return res;
}
std::tuple<int, int> get_guard_pos(std::vector<std::string>& guard_map) {
    for (int row = 0; row < guard_map.size(); row++) {
        for (int col = 0; col < guard_map.at(row).length(); col++) {
            switch (guard_map.at(row).at(col)) {
                case '^':
                    return std::make_tuple(row, col);
                    break;
                case '>':
                    return std::make_tuple(row, col);
                    break;
                case '<':
                    return std::make_tuple(row, col);
                    break;
                case 'v':
                    return std::make_tuple(row, col);
                    break;
                default:
                    break;
            }
        }
    }
    throw std::runtime_error("Guard not found in map!");
}
void move_guard(std::vector<std::string>& guard_map) {
    std::tuple<int, int> current_pos = get_guard_pos(guard_map);
    int rise;
    int run;
    char turn_char;
    while (true) {
        switch (guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos))) {
            case '^':
                rise = 1, run = 0, turn_char = '>';
                break;
            case '>':
                rise = 0, run = 1, turn_char = 'v';
                break;
            case 'v':
                rise = -1, run = 0, turn_char = '<';
                break;
            case '<':
                rise = 0, run = -1, turn_char = '^';
                break;
            default:
                throw std::runtime_error("Current pos not a guard -> " + std::to_string(std::get<0>(current_pos)) + " | " + std::to_string(std::get<1>(current_pos)));
                break;
        }
        if (std::get<0>(current_pos) + -rise < 0
            || std::get<0>(current_pos) + -rise >= guard_map.size()
            || std::get<1>(current_pos) + run < 0
            || std::get<1>(current_pos) + run >= guard_map.front().length()) {
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = 'X';
            break;
        } else if (guard_map.at(std::get<0>(current_pos) + -rise).at(std::get<1>(current_pos) + run) == '#') {
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = turn_char;
        } else {
            guard_map.at(std::get<0>(current_pos) + -rise).at(std::get<1>(current_pos) + run) = guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos));
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = 'X';
            current_pos = std::make_tuple(std::get<0>(current_pos) + -rise, std::get<1>(current_pos) + run);
        }
    }
}

std::set<std::tuple<int, int>> move_guard_get_travelled(std::vector<std::string>& guard_map) {
    std::tuple<int, int> current_pos = get_guard_pos(guard_map);
    int rise;
    int run;
    char turn_char;
    std::set<std::tuple<int, int>> travelled_pos = {};
    while (true) {
        travelled_pos.insert(current_pos);
        switch (guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos))) {
            case '^':
                rise = 1, run = 0, turn_char = '>';
                break;
            case '>':
                rise = 0, run = 1, turn_char = 'v';
                break;
            case 'v':
                rise = -1, run = 0, turn_char = '<';
                break;
            case '<':
                rise = 0, run = -1, turn_char = '^';
                break;
            default:
                throw std::runtime_error("Current pos not a guard -> " + std::to_string(std::get<0>(current_pos)) + " | " + std::to_string(std::get<1>(current_pos)));
                break;
        }
        if (std::get<0>(current_pos) + -rise < 0
            || std::get<0>(current_pos) + -rise >= guard_map.size()
            || std::get<1>(current_pos) + run < 0
            || std::get<1>(current_pos) + run >= guard_map.front().length()) {
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = 'X';
            break;
        } else if (guard_map.at(std::get<0>(current_pos) + -rise).at(std::get<1>(current_pos) + run) == '#') {
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = turn_char;
        } else {
            guard_map.at(std::get<0>(current_pos) + -rise).at(std::get<1>(current_pos) + run) = guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos));
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = 'X';
            current_pos = std::make_tuple(std::get<0>(current_pos) + -rise, std::get<1>(current_pos) + run);
        }
    }
    return travelled_pos;
}

bool move_guard_does_loop(std::vector<std::string>& guard_map, std::tuple<int, int> block_pos) {
    guard_map.at(std::get<0>(block_pos)).at(std::get<1>(block_pos)) = '#';
    std::tuple<int, int> current_pos = get_guard_pos(guard_map);
    std::map<std::tuple<int, int>, std::set<char>> visited_map = {};
    int rise;
    int run;
    char turn_char;
    while (true) {
        switch (guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos))) {
            case '^':
                rise = 1, run = 0, turn_char = '>';
                break;
            case '>':
                rise = 0, run = 1, turn_char = 'v';
                break;
            case 'v':
                rise = -1, run = 0, turn_char = '<';
                break;
            case '<':
                rise = 0, run = -1, turn_char = '^';
                break;
            default:
                throw std::runtime_error("Current pos not a guard -> " + std::to_string(std::get<0>(current_pos)) + " | " + std::to_string(std::get<1>(current_pos)));
                break;
        }
        if (!visited_map.count(current_pos)) {
            visited_map.insert({ current_pos, {guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos))} });
        } else if (visited_map.at(current_pos).count(guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)))) {
            return true;
        } else {
            visited_map.at(current_pos).insert(guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)));
        }
        if (std::get<0>(current_pos) + -rise < 0
            || std::get<0>(current_pos) + -rise >= guard_map.size()
            || std::get<1>(current_pos) + run < 0
            || std::get<1>(current_pos) + run >= guard_map.front().length()) {
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = 'X';
            break;
        } else if (guard_map.at(std::get<0>(current_pos) + -rise).at(std::get<1>(current_pos) + run) == '#') {
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = turn_char;
        } else {
            guard_map.at(std::get<0>(current_pos) + -rise).at(std::get<1>(current_pos) + run) = guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos));
            guard_map.at(std::get<0>(current_pos)).at(std::get<1>(current_pos)) = 'X';
            current_pos = std::make_tuple(std::get<0>(current_pos) + -rise, std::get<1>(current_pos) + run);
        }
    }
    return false;
}

int part_1() {
    std::vector<std::string> guard_map = UTILS::get_input("input/day_6.txt");
    move_guard(guard_map);
    return count_in_2d_vec(guard_map, 'X');
}
int part_2() { // i know it's not good but it works so shut up
    // i could probably get this down to n^2
    // traverse the original map assuming it doesn't loop and proactively put blockers in the way of every next step
    // test with the blocker in the next step of the original map.
    // move onto the next step of the original map.
    // repeat until the original map ends
    // You could also pass already travelled positions from the original.
    // oh well
    std::vector<std::string> guard_map = UTILS::get_input("input/day_6.txt");
    std::vector<std::string> original_map(guard_map);
    std::set<std::tuple<int, int>> travelled_pos = move_guard_get_travelled(guard_map);
    travelled_pos.erase(get_guard_pos(original_map));
    int res = 0;
    for (std::tuple<int, int> pos : travelled_pos) {
        guard_map = original_map;
        res += move_guard_does_loop(guard_map, pos);
    }
    return res;
}

void solve() {
    // std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}
