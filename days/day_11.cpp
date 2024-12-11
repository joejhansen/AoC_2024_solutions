#include "day_11.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<unsigned long long> blink(std::vector<unsigned long long> stones) { // do you want to be fast and fat?
    // i thought about doing it in place but then that sounds like a nightmare so
    std::vector<unsigned long long> res = {};
    for (unsigned long long stone : stones) {
        if (stone == 0) {
            res.push_back(1);
        } else { // i know but i feel bad about doing to_string and then immediately throwing it away
            std::string stone_string = std::to_string(stone);
            if (stone_string.length() % 2 == 0) {
                // std::cout << stone << std::endl;
                res.push_back(stoull(stone_string.substr(0, stone_string.length() / 2)));
                res.push_back(stoull(stone_string.substr(stone_string.length() / 2, stone_string.length() / 2)));
            } else {
                res.push_back(stone * 2024ull);
            }
        }
    }
    return res;
}
std::vector<unsigned long long> blink_n_times(std::vector<unsigned long long> stones, int n) {
    for (int i = 0; i < n; i++) {
        stones = blink(stones);
    }
    return stones;
}


int part_1() {
    std::vector<unsigned long long> stones = UTILS::split_string_to_unsigned_long_longs(UTILS::get_input("input/day_11.txt")[0], ' ');
    stones = blink_n_times(stones, 25);
    return stones.size();
}

void blink_in_place(std::vector<unsigned long long>& stones) { // or do you want to be lean and slow?
    for (int i = 0;;i++) {
        if (i >= stones.size()) {
            break;
        }
        if (stones[i] == 0) {
            stones[i] = 1;
        } else {
            std::string stone_string = std::to_string(stones[i]);
            if (stone_string.length() % 2 == 0) {
                // std::cout << stone << std::endl;
                stones.erase(stones.begin() + i);
                stones.insert(stones.begin() + i, stoull(stone_string.substr(stone_string.length() / 2, stone_string.length() / 2)));
                stones.insert(stones.begin() + i, stoull(stone_string.substr(0, stone_string.length() / 2)));
            } else {
                stones[i] = stones[i] * 2024ull;
            }
        }
    }
}

std::vector<unsigned long long> blink_better(std::vector<unsigned long long> stones) {
    std::vector<unsigned long long> res = {};
    for (int i = stones.size() - 1; i >= 0; i--) {
        if (stones[i] == 0) {
            res.push_back(1);
        } else { // i know but i feel bad about doing to_string and then immediately throwing it away
            std::string stone_string = std::to_string(stones[i]);
            if (stone_string.length() % 2 == 0) {
                // std::cout << stone << std::endl;
                res.push_back(stoull(stone_string.substr(0, stone_string.length() / 2)));
                res.push_back(stoull(stone_string.substr(stone_string.length() / 2, stone_string.length() / 2)));
            } else {
                res.push_back(stones[i] * 2024ull);
            }
        }
        stones.pop_back();
    }
    std::reverse(res.begin(), res.end());
    return res;
}
std::vector<unsigned long long> blink_better_n_times(std::vector<unsigned long long> stones, int n) {
    for (int i = 0; i < n; i++) {
        stones = blink_better(stones);
    }
    return stones;
}
void blink_in_place_n_times(std::vector<unsigned long long>& stones, int n) {
    for (int i = 0; i < n; i++) {
        blink_in_place(stones);
    }
}

int part_2() {
    std::vector<unsigned long long> stones = UTILS::split_string_to_unsigned_long_longs(UTILS::get_input("input/day_11.txt")[0], ' ');
    stones = blink_better_n_times(stones, 75);
    return stones.size();
}
void solve() {
    // std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}