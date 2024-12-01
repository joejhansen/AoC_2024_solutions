#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "day_1.h"

std::vector<std::string> get_input()
{
    std::vector<std::string> file_contents = {};
    std::string file_name = "day_1.txt";
    std::ifstream file(file_name);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            file_contents.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << file_name << std::endl;
    }
    return file_contents;
}

std::tuple<std::vector<int>, std::vector<int>> get_sorted_lists(std::vector<std::string> input)
{
    std::vector<int> listL = {};
    std::vector<int> listR = {};
    for (std::string line : input)
    {
        std::tuple<int, int> int_pair = get_pair(line);
        listL.push_back(std::get<0>(int_pair));
        listR.push_back(std::get<1>(int_pair));
    }
    sort(listL.begin(), listL.end());
    sort(listR.begin(), listR.end());
    return std::make_tuple(listL, listR);
}

std::tuple<int, int> get_pair(std::string input)
{
    std::string val1;
    std::string val2;
    bool first = true;
    for (char c : input)
    {
        if (c == ' ')
        {
            first = false;
            continue;
        }
        if (first)
        {
            val1 = val1 + c;
        }
        else
        {
            val2 = val2 + c;
        }
    }
    return std::make_tuple(stoi(val1), stoi(val2));
}

int day_1_part_1()
{
    std::vector<std::string> pairs = get_input();
    std::tuple<std::vector<int>, std::vector<int>> sorted_lists = get_sorted_lists(pairs);
    int distance = 0;
    for (int i = 0; i < std::get<0>(sorted_lists).size(); i++)
    {
        distance += abs(std::get<0>(sorted_lists)[i] - std::get<1>(sorted_lists)[i]);
    }
    return distance;
}

int day_1_part_2()
{
    std::tuple<std::vector<int>, std::vector<int>> sorted_lists = get_sorted_lists(get_input());
    std::map<int, int> occ_map = {};
    int result = 0;
    for (int left_val : std::get<0>(sorted_lists))
    {
        if (occ_map.count(left_val))
        {
            result += left_val * occ_map.at(left_val);
        }
        else
        {
            occ_map.insert({left_val, std::count(std::get<1>(sorted_lists).begin(), std::get<1>(sorted_lists).end(), left_val)});
            result += left_val * occ_map.at(left_val);
        }
    }
    return result;
}