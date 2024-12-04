#include <iostream>
#include <cmath>
#include "day_4.h"
#include "utils.h"

int how_many_crossword(std::vector<std::string>* input_field, int row, int column, std::string match_to) {
    int rise; // keep in mind +1 rise is -1 index
    int run;  // keep in mind +1 run  is +1 index
    int res = 0;
    for (int i = 0; i < 9; i++) {
        if (i == 4) {
            continue;
        }
        switch (i) { // judge not lest ye be judged
            case 0:
                rise = 1;
                run = -1;
                break;
            case 1:
                rise = 1;
                run = 0;
                break;
            case 2:
                rise = 1;
                run = 1;
                break;
            case 3:
                rise = 0;
                run = -1;
                break;
            case 4:
                // should be unreachable
                break;
            case 5:
                rise = 0;
                run = 1;
                break;
            case 6:
                rise = -1;
                run = -1;
                break;
            case 7:
                rise = -1;
                run = 0;
                break;
            case 8:
                rise = -1;
                run = 1;
                break;
            default:
                break;
        }
        if (row + (rise * -1 * (match_to.length() - 1)) < 0
            || row + (rise * -1 * (match_to.length() - 1)) >= input_field->size()
            || column + (run * (match_to.length() - 1)) < 0
            || column + (run * (match_to.length() - 1)) >= input_field->front().length()) {
            continue;
        } else {
            bool failed = false;
            for (int j = 0; j < match_to.length(); j++) {
                if (input_field->at(row + (rise * -1 * j)).at(column + (run * j)) != match_to[j]) {
                    failed = true;
                    break;
                };
            }
            if (!failed) {
                res += 1;
            }
        }

    }
    return res;
}
int get_x_word_shift(int n) {
    return std::floor(n / 2) * (n % 2 == 0 ? 1 : -1);
}
bool has_x_word(std::vector<std::string>* input_field, int row, int column, std::string match_to) { // only works with odd length
    int res = 0;
    int rise;
    int run;
    int middle_index = std::floor((match_to.length() - 1) / 2);
    if (row - middle_index < 0
        || row + middle_index >= input_field->size()
        || column - middle_index < 0
        || column + middle_index >= input_field->front().length()
        ) { // bounds check
        return false;
    }
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                rise = 1;
                run = -1;
                break;
            case 1:
                rise = 1;
                run = 1;
                break;
            case 2:
                rise = -1;
                run = -1;
                break;
            case 3:
                rise = -1;
                run = 1;
                break;
            default:
                break;
        }
        bool failed = false;
        for (int j = 0; j < match_to.length(); j++) {
            if (input_field->at(row + (get_x_word_shift(j + 1) * -rise)).at(column + (get_x_word_shift(j + 1) * run)) != match_to.at(middle_index + get_x_word_shift(j + 1))) {
                failed = true;
                break;
            }
        }
        if (!failed) {
            res += 1;
        }
    }
    return res >= 2;
}
int part_1() {
    std::vector<std::string> input = UTILS::get_input("input/day_4.txt");
    int res = 0;
    for (int row = 0; row < input.size(); row++) {
        for (int column = 0; column < input[row].length();column++) {
            if (input[row][column] == 'X') res += how_many_crossword(&input, row, column, "XMAS");
        }
    }
    return res;
}
int part_2() {
    std::vector<std::string> input = UTILS::get_input("input/day_4.txt");
    int res = 0;
    for (int row = 0; row < input.size(); row++) {
        for (int column = 0; column < input[row].length();column++) {
            if (input[row][column] == 'A') res += has_x_word(&input, row, column, "MAS");
        }
    }
    return res;
}
void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}
