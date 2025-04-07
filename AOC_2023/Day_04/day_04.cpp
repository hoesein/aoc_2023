#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>
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

int part_one()
{
    std::vector<std::string> lines = read_file();

    if (lines.empty())
    {
        std::cerr << "No data on file." << std::endl;
    }

    std::vector<int> result;
    std::vector<std::string> num_list;
    std::vector<int> win_num;
    std::vector<int> my_num;

    for (int i = 0; i < lines.size(); i++)
    {
        num_list.push_back(tools::separator(lines[i], ":")[1]);

        for (int j = 0; j < num_list.size(); j++)
        {
            win_num = tools::remove<int>(tools::separator(num_list[j], "|")[0], ' ');
            my_num = tools::remove<int>(tools::separator(num_list[j], "|")[1], ' ');

            int win_count = 0;
            for (int my : my_num)
            {
                if (std::find(win_num.begin(), win_num.end(), my) != win_num.end())
                {
                    win_count += 1;
                }
            }

            if (win_count == 0)
                continue;

            result.push_back(pow(2, win_count - 1));
        }
        num_list.clear();
    }

    return std::accumulate(result.begin(), result.end(), 0);
}

int part_two()
{
    std::vector<std::string> lines = read_file();

    if (lines.empty())
    {
        std::cerr << "No data on file." << std::endl;
    }

    std::vector<std::string> num_list;
    std::vector<int> win_num;
    std::vector<int> my_num;

    std::vector<int> cards;
    for (int _ = 0; _ < lines.size(); _++)
        cards.push_back(1);

    for (int i = 0; i < lines.size(); i++)
    {
        num_list.push_back(tools::separator(lines[i], ":")[1]);

        for (int j = 0; j < num_list.size(); j++)
        {
            win_num = tools::remove<int>(tools::separator(num_list[j], "|")[0], ' ');
            my_num = tools::remove<int>(tools::separator(num_list[j], "|")[1], ' ');

            int win_count = 0;
            for (int my : my_num)
            {
                if (std::find(win_num.begin(), win_num.end(), my) != win_num.end())
                {
                    win_count += 1;
                }
            }

            for (int z = i + 1; z < i + 1 + win_count; z++)
            {
                cards[z] += cards[i];
            }
        }
        num_list.clear();
    }

    return std::accumulate(cards.begin(), cards.end(), 0);
}

int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    int p1 = part_one();
    int p2 = part_two();

    std::cout << "Part One: " << p1 << std::endl;
    std::cout << "Part Two: " << p2 << std::endl;

    auto stop = high_resolution_clock::now();
    auto dura = duration_cast<milliseconds>(stop - start);
    std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

    return 0;
}
