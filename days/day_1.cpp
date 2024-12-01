#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "day_1.h"

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
    const std::string SEPERATOR = "   ";
    std::vector<std::string> pairs = {};
    std::string file_name = "day_1.txt";
    std::ifstream file(file_name);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            pairs.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << file_name << std::endl;
    }
    int distance = 0;
    for (std::string pair : pairs)
    {
        std::tuple<int, int> this_pair = get_pair(pair);
        distance += std::abs(std::get<0>(this_pair) - std::get<1>(this_pair));
    }
    return distance;
}