#include <iostream>
#include "day_4.h"
#include "utils.h"

int how_many_crossword(std::vector<std::string>* input_field, int row, int column, std::string match_to) {
    int rise; // keep in mind +1 rise is -1 index
    int run; // keep in mind +1 run  is +1 index
    int res = 0;
    for (int i = 0; i < 9; i++) {
        if (i == 4){
            continue;
        }
        switch (i) {
            case 0:
                rise = 1;
                run = -1;
                break;
            case 1:
                rise = 1;
                run = 0;
                /* code */
                break;
            case 2:
                rise = 1;
                run = 1;
                /* code */
                break;
            case 3:
                rise = 0;
                run = -1;
                /* code */
                break;
            case 4:
                /* code */
                break;
            case 5:
                rise = 0;
                run = 1;
                break;
            case 6:
                rise = -1;
                run = -1;
                /* code */
                break;
            case 7:
                rise = -1;
                run = 0;
                /* code */
                break;
            case 8:
                rise = -1;
                run = 1;
                /* code */
                break;
            default:
                break;
        }
        if (row + (rise * -1 * (match_to.length() - 1)) < 0
            || row + (rise * -1 * (match_to.length() - 1)) >= input_field->size()
            || column + (run * (match_to.length() - 1) ) < 0
            || column + (run * (match_to.length() - 1) ) >= input_field->front().length()) {
            continue;
        } else {
            bool failed = false;
            for (int j = 0; j < match_to.length(); j++) {
                // char something = input_field->at(0).at(0);
                // if (input_field[0][0] == match_to[0]){}
                // column + (rise * -1 * j)
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

int part_1() {
    std::vector<std::string> input = UTILS::get_input("input/day_4.txt");
    int res = 0;
    for (int row = 0; row < input.size(); row++) {
        for (int column = 0; column < input[row].length();column++) {
            // std::cout << row + ":" + column << std::endl;
            if (input[row][column] == 'X') res += how_many_crossword(&input, row, column, "XMAS");
        }
    }
    return res;
}
int part_2() {
    return 0;
}
void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}
