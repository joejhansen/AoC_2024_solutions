#include "day_5.h"
#include "utils.h"
#include <tuple>
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <cmath>
#include <iostream>
#include <algorithm>

std::vector<int> split_str_to_ints(std::string& input, char delimiter) {
    std::istringstream stream(input);
    std::vector<int> tokens;
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(std::stoi(token));
    }
    return tokens;
}
bool passes_rules(std::string& rule_str, std::vector<int> update_ints, std::map<int, std::set<int>>& rule_map) {
    std::set<int> behind_set = {};
    for (int i = 1; i < update_ints.size(); i++) {
        behind_set.insert(update_ints[i - 1]);
        if (rule_map.count(update_ints[i])) {
            for (int must_be_ahead : rule_map.at(update_ints[i])) {
                if (behind_set.count(must_be_ahead)) {
                    return false;
                }
            }
        }
    }
    return true;
}
std::tuple<int, int> get_rule_ints(std::string rule) {
    return std::make_tuple(std::stoi(rule.substr(0, rule.find('|'))), std::stoi(rule.substr(rule.find('|') + 1, rule.length() - rule.find('|') - 1)));
}
int part_1() {
    std::vector<std::string> rules = UTILS::get_input("input/day_5_p1.txt");
    std::vector<std::string> update_strs = UTILS::get_input("input/day_5_p2.txt");
    std::map<int, std::set<int>> rule_map = {};
    int res = 0;
    for (std::string rule : rules) {
        std::tuple<int, int> rule_ints = get_rule_ints(rule);
        if (rule_map.count(std::get<0>(rule_ints))) {
            rule_map.at(std::get<0>(rule_ints)).insert(std::get<1>(rule_ints));
        } else {
            rule_map.insert({ std::get<0>(rule_ints), {std::get<1>(rule_ints)} });
        }
    }
    for (std::string update : update_strs) {
        std::vector<int> update_ints = split_str_to_ints(update, ',');
        if (passes_rules(update, update_ints, rule_map)) {
            res += update_ints.at(std::floor(update_ints.size() / 2));
        }
    }
    return res;
}

std::vector<int> make_correct_order(std::vector<int> bad_ints, std::map<int, std::set<int>>& rule_map) {
    std::sort(bad_ints.begin(), bad_ints.end(), [&](int a, int b) {
        if (rule_map.count(b) == 0) {
            return true;
        }
        if (find(rule_map.at(b).begin(), rule_map.at(b).end(), a) != rule_map.at(b).end()) {
            return true;
        } else {
            return false;
        }
        });
    return bad_ints;
}

int part_2() {
    std::vector<std::string> rules = UTILS::get_input("input/day_5_p1.txt");
    std::vector<std::string> update_strs = UTILS::get_input("input/day_5_p2.txt");
    std::map<int, std::set<int>> rule_map = {};
    int res = 0;
    for (std::string rule : rules) {
        std::tuple<int, int> rule_ints = get_rule_ints(rule);
        if (rule_map.count(std::get<0>(rule_ints))) {
            rule_map.at(std::get<0>(rule_ints)).insert(std::get<1>(rule_ints));
        } else {
            rule_map.insert({ std::get<0>(rule_ints), {std::get<1>(rule_ints)} });
        }
    }
    for (std::string update : update_strs) {
        std::vector<int> update_ints = split_str_to_ints(update, ',');
        if (!passes_rules(update, update_ints, rule_map)) {
            res += make_correct_order(update_ints, rule_map).at(std::floor(update_ints.size() / 2));
        }
    }
    return res;
}

void solve() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
}
