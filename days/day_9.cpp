#include "day_9.h"
#include "utils.h"
#include <iostream>
#include <stdexcept>


std::vector<long> get_fragmented_file_block(std::string input_str) {
    std::vector<long> res = {};
    long curr_id = 0;
    for (long op_index = 0; op_index < input_str.length(); op_index++) {
        for (int _ = 0; _ < (input_str[op_index] - '0');_++) {
            if (op_index % 2 == 0) {
                res.push_back(curr_id);
            } else {
                // empty space represented by -1 because . aint an int
                res.push_back(-1);
            }
        }
        if (op_index % 2 == 0) curr_id++;
    }
    return res;
}

void defrag_file_block(std::vector<long>& file_block) {
    int index_left = 0;
    int index_right = file_block.size() - 1;
    while (index_left < index_right) {
        if (file_block[index_left] < 0 && file_block[index_right] >= 0) {
            file_block[index_left] = file_block[index_left] ^ file_block[index_right];
            file_block[index_right] = file_block[index_right] ^ file_block[index_left];
            file_block[index_left] = file_block[index_left] ^ file_block[index_right];
            index_left++;
            index_right--;
            continue;
        }
        while (file_block[index_right] < 0) index_right--;
        while (file_block[index_left] >= 0) index_left++;
    }
}

unsigned long long calculate_checksum(std::vector<long>& file_block) {
    unsigned long long res = 0;
    for (long i = 0; i < file_block.size(); i++) {
        if (file_block[i] < 0) {
            break;
        }
        res += i * file_block[i];
    }
    return res;
}

unsigned long long part_1() {
    std::string input = get_input("input/day_9.txt")[0];
    std::vector<long> file_block = get_fragmented_file_block(input);
    defrag_file_block(file_block);
    return calculate_checksum(file_block);
}

void defrag_file_block_dont_break(std::vector<long>& file_block) {
    int current_id = -1;
    for (int i = file_block.size() - 1; i >= 0; i--) {
        if (file_block[i] == -1) continue;
        else {
            current_id = file_block[i];
            break;
        }
    }
    if (current_id == -1) throw std::runtime_error("Something went wrong finding the first index and id");
    for (; current_id >= 0; current_id--) {
        int curr_block_size = 0;
        int curr_index = 0;
        for (int i = file_block.size() - 1; i >= 0; i--) {
            if (file_block[i] == current_id) {
                curr_block_size++;
                curr_index = i;
            }
        }

        int curr_free_space = 0;
        int curr_free_index = -1;
        for (int i = 0; i < curr_index; i++) {
            if (file_block[i] != -1) {
                curr_free_space = 0;
            } else {
                curr_free_space++;
                curr_free_index = i;
                if (curr_free_space >= curr_block_size) break;
            }
        }
        if (curr_free_space < curr_block_size) continue;
        for (int i = 0; i < curr_free_space; i++) {
            file_block[curr_free_index - i] = current_id;
        }
        for (int i = 0; i < curr_free_space; i++) {
            file_block[curr_index + i] = -1;
        }
    }
}

unsigned long long calculate_checksum_whole_system(std::vector<long>& file_block) {
    unsigned long long res = 0;
    for (long i = 0; i < file_block.size(); i++) {
        if (file_block[i] < 0) {
            continue;
        }
        res += i * file_block[i];
    }
    return res;
}

unsigned long long part_2() {
    std::string input = get_input("input/day_9.txt")[0];
    std::vector<long> file_block = get_fragmented_file_block(input);
    defrag_file_block_dont_break(file_block);
    return calculate_checksum_whole_system(file_block);
}
void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}