#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <numeric>
#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("input.txt");
    if (!input_file.is_open())
    {
        std::cerr << "Error opening file\n";
        return {};
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

struct Rule
{
    uint64_t time;
    uint64_t distance;
};

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if (!lines.empty())
    {
        std::cerr << "No data found." << std::endl;
    }

    std::vector<std::vector<int>> digits;
    for (int i = 0; i < lines.size(); i++)
    {
        std::vector<std::string> str = tools::separator(lines[i], ":");
        digits.push_back(tools::remove<int>(str[1], ' '));
    }

    std::vector<Rule> rules;
    for (int i = 0; i < digits[0].size(); i++)
    {
        Rule rule;
        rule.time = digits[0][i];
        rule.distance = digits[1][i];
        rules.push_back(rule);
    }

    std::vector<int> result;
    for (Rule &rule : rules)
    {
        int possible_count = 0;
        for (int i = 1; i < rule.time; i++)
        {
            if ((rule.time - i) * i > rule.distance)
            {
                possible_count++;
            }
        }
        result.push_back(possible_count);
    }

    int answer = 1;
    for (int i = 0; i < result.size(); i++)
    {
        answer *= result[i];
    }
    return std::to_string(answer);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if (!lines.empty())
    {
        std::cerr << "No data found." << std::endl;
    }

    std::vector<std::vector<std::string>> digits;
    for (int i = 0; i < lines.size(); i++)
    {
        std::vector<std::string> str = tools::separator(lines[i], ":");
        digits.push_back(tools::remove<std::string>(str[1], ' '));
    }

    std::vector<std::vector<int>> digit_numeric;
    std::string time_str, distance_str;
    for (int i = 0; i < digits[0].size(); i++)
    {
        time_str += digits[0][i];
        distance_str += digits[1][i];
    }

    Rule rule = {std::stoull(time_str), std::stoull(distance_str)};

    int possible_count = 0;
    for (int i = 1; i < rule.time; i++)
    {
        if ((rule.time - i) * i > rule.distance)
        {
            possible_count++;
        }
    }

    return std::to_string(possible_count);
}

int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    std::string p1 = part_one();
    std::string p2 = part_two();

    std::cout << "Part One: " << p1 << std::endl;
    std::cout << "Part Two: " << p2 << std::endl;

    auto stop = high_resolution_clock::now();
    auto dura = duration_cast<milliseconds>(stop - start);
    std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

    return 0;
}
