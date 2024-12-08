#include "day_7.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>
#include <cmath>
#include <algorithm>

// we're gonna think of this like building a binary number, but with + and * instead of 0 and 1
// if there ar 7 parts, that's a 6 bit value
// bits = parts.length - 1;

std::string increment_operations(std::string operations) {
    // big endian, doesn't really matter which way but it's easier for me to think like this
    for (int i = operations.length() - 1; i >= 0; i--) {
        if (operations[i] == '+') {
            operations[i] = '*';
            break;
        } else if (operations[i] == '*') {
            operations[i] = '+';
            continue;
        } else {
            throw std::runtime_error("Operation at index isn't * or +!");
        }
    }
    return operations;
}
std::string build_first_operation(int length) {
    std::string res = "";
    for (int i = 0; i < length; i++) {
        res = res + '+';
    }
    return res;
}
std::string build_first_operation(int length, char first_bit) {
    std::string res = "";
    for (int i = 0; i < length; i++) {
        res = res + first_bit;
    }
    return res;
}
std::string increment_operations(std::string operations, std::string op_ranks) {
    for (int i = 0; i < operations.length(); i++) {

        auto maybe_value = std::find(op_ranks.begin(), op_ranks.end(), operations[i]);
        if (maybe_value == op_ranks.end()) {
            throw std::runtime_error("Operation not in ranks!");
        }

        auto index_of = maybe_value - op_ranks.begin();
        if (index_of < 0 || index_of > op_ranks.size() - 1) {
            throw std::runtime_error("Index of op_ranks out of bounds!");
        }

        if (index_of == op_ranks.size() - 1) {
            operations[i] = op_ranks.front();
        } else {
            operations[i] = op_ranks[index_of+1];
            break;
        }
    }
}
bool is_operation_maxed(std::string operation) {
    for (char ch : operation) {
        if (ch == '+') {
            return false;
        } else if (ch == '*') {
            continue;
        } else {
            throw std::runtime_error("Operation is invalid!");
        }
    }
    return true;
}
bool is_operation_maxed(std::string operation, std::vector<char> op_ranks) {
    for (char ch : operation) {
        auto maybe_value = std::find(op_ranks.begin(), op_ranks.end(), ch);
        if (maybe_value == op_ranks.end()) {
            throw std::runtime_error("Operation not in ranks!");
        }
        if (ch == op_ranks.back()) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

// Returns the sum if a valid operation set is found, 0 if not.
unsigned long long does_part_build_to_sum_how_much(unsigned long long sum, std::vector<unsigned long long> parts) {
    std::string curr_operations = build_first_operation(parts.size() - 1);
    unsigned long long loop_checker = 0; // this should take no more than 2^operations.size() iterations
    unsigned long long max_loops = pow(2, curr_operations.size()) + 1;
    while (true) {
        unsigned long long tmp_sum = parts.front();
        for (int i = 1; i < parts.size(); i++) {
            if (curr_operations[i - 1] == '+') {
                tmp_sum = tmp_sum + parts[i];
            } else if (curr_operations[i - 1] == '*') {
                tmp_sum = tmp_sum * parts[i];
            } else {
                throw std::runtime_error("Found an invalid operation!");
            }
        }
        if (tmp_sum == sum) {
            return tmp_sum;
        } else if (is_operation_maxed(curr_operations)) {
            break;
        } else {
            curr_operations = increment_operations(curr_operations);
        }
        if (loop_checker++ >= max_loops) {
            throw std::runtime_error("Too many loops!");
        }
    }
    return 0;
}
std::string increment_operations_part_2(std::string operations) {
    // big endian, doesn't really matter which way but it's easier for me to think like this
    for (int i = operations.length() - 1; i >= 0; i--) {
        if (operations[i] == '+') {
            operations[i] = '|';
            break;
        } else if (operations[i] == '|') {
            operations[i] = '*';
            break;
        } else if (operations[i] == '*') {
            operations[i] = '+';
            continue;
        } else {
            throw std::runtime_error("Operation at index isn't +, *, or | !");
        }
    }
    return operations;
}

bool is_operation_maxed_part_2(std::string operation) {
    for (char ch : operation) {
        if (ch == '+' || ch == '|') {
            return false;
        } else if (ch == '*') {
            continue;
        } else {
            throw std::runtime_error("Operation is invalid!");
        }
    }
    return true;
}


unsigned long long does_part_build_to_sum_how_much_part_2(unsigned long long sum, std::vector<unsigned long long> parts) {
    std::string curr_operations = build_first_operation(parts.size() - 1, '+');
    unsigned long long loop_checker = 0; // this should take no more than 2^operations.size() iterations
    unsigned long long max_loops = pow(3, curr_operations.size()) + 1;
    while (true) {
        unsigned long long tmp_sum = parts.front();
        for (int i = 1; i < parts.size(); i++) {
            if (curr_operations[i - 1] == '+') {
                tmp_sum = tmp_sum + parts[i];
            } else if (curr_operations[i - 1] == '*') {
                tmp_sum = tmp_sum * parts[i];
            } else if (curr_operations[i - 1] == '|') {
                tmp_sum = stoull(std::to_string(tmp_sum) + std::to_string(parts[i]));
            } else {
                throw std::runtime_error("Found an invalid operation!");
            }
        }
        if (tmp_sum == sum) {
            return tmp_sum;
        } else if (is_operation_maxed_part_2(curr_operations)) {
            break;
        } else {
            curr_operations = increment_operations_part_2(curr_operations);
        }
        if (loop_checker++ >= max_loops) {
            throw std::runtime_error("Too many loops!");
        }
    }
    return 0;
}

std::tuple<unsigned long long, std::vector<unsigned long long>> get_sum_and_parts(std::string input) {
    std::vector<std::string> tmp = UTILS::split_string(input, ':');
    unsigned long long sum = stoull(tmp.front());
    tmp.erase(tmp.begin());
    tmp = UTILS::split_string(tmp.front(), ' ');
    std::vector<unsigned long long> parts = {};
    for (std::string part : tmp) {
        parts.push_back(stoull(part));
    }
    return std::make_tuple(sum, parts);

}

unsigned long long part_1() {
    std::vector<std::string> input = UTILS::get_input("input/day_7.txt");
    unsigned long long res = 0;
    for (std::string line : input) {
        std::tuple<unsigned long long, std::vector<unsigned long long>> sum_and_parts = get_sum_and_parts(line);
        unsigned long long prev_res = res;
        res += does_part_build_to_sum_how_much(std::get<0>(sum_and_parts), std::get<1>(sum_and_parts));
    }
    return res;
}

unsigned long long part_2() { // this takes a loooooooooooooooooooooooong time, but it works!
    std::vector<std::string> input = UTILS::get_input("input/day_7_example.txt");
    unsigned long long res = 0;
    for (std::string line : input) {
        std::tuple<unsigned long long, std::vector<unsigned long long>> sum_and_parts = get_sum_and_parts(line);
        unsigned long long prev_res = res;
        res += does_part_build_to_sum_how_much_part_2(std::get<0>(sum_and_parts), std::get<1>(sum_and_parts));
    }
    return res;
}


void solve() {
    // std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}
