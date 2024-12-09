#include "day_9.h"
#include "utils.h"
#include <iostream>
#include <stdexcept>


std::vector<long> get_fragmented_file_block(std::string input_str) {
    std::vector<long> res = {};
    long curr_id = 0;
    // for (char o){}
    for (long op_index = 0; op_index < input_str.length(); op_index++) {
        for (int _ = 0; _ < (input_str[op_index] - '0');_++) {
            if (op_index % 2 == 0) {
                // file block
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
void defrag_file_block(std::vector<long>& file_block) { // something wrong here
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

void defrag_file_block_dont_break(std::vector<long>& file_block) { // something wrong here 
    // TODO: Fix this tomorrow
    int curr_id = -1;
    int curr_index = -1;
    for (int i = file_block.size() - 1; i >= 0; i--) {
        if (file_block[i] >= 0) {
            curr_id = file_block[i];
            curr_index = i;
            break;
        }
    }
    // std::vector<int> curr_block = {};
    int curr_block_size = 0;
    while (curr_id >= 0 && curr_index >= 0) {
        while (file_block[curr_index] == curr_id) {
            // curr_block.push_back(curr_id);
            curr_block_size++;
            curr_index--;
        }
        int empty_block_size = 0;
        int empty_block_index = 0;
        for (int i = 0; i < curr_index - curr_block_size;i++) {
            if (file_block[i] < 0) {
                empty_block_size++;
                if (empty_block_size >= curr_block_size) {
                    empty_block_index = i;
                }
            }
        }
        for (int i = 0; i < curr_block_size;i++) {
            file_block[empty_block_index - i] = curr_id;
        }
        for (int i = 0; i < curr_block_size;i++) {
            file_block[curr_index + i] = -1;
        }
        curr_id--;
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
    std::string input = get_input("input/day_9_example.txt")[0];
    std::vector<long> file_block = get_fragmented_file_block(input);
    defrag_file_block_dont_break(file_block);
    for (int block : file_block) {
        std::cout << std::to_string(block) << std::endl;
    }
    return calculate_checksum_whole_system(file_block);
}
void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}