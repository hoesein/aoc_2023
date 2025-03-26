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

namespace tools
{
    bool contain(std::string word, std::string separator)
    {
        int result = word.find(separator);
        if ((result >= 0) && (result <= word.length()))
        {
            return true;
        }
        else if (result == std::string::npos)
        {
            return false;
        }
        else
        {
            return false;
        }
    }

    std::vector<std::string> separator(std::string input, std::string separator = ",")
    {
        std::vector<std::string> separated_string = {};
        std::string word;

        if (separator.length() == 1)
        {
            std::istringstream split(input);

            // for (std::string each; std::getline(split, each, separator[0]); separated_string.push_back(each));

            std::string each;
            while (std::getline(split, each, separator[0]))
            {
                separated_string.push_back(each);
            }

            if (separated_string.empty())
            {
                if (separated_string.back().back() == separator[0])
                {
                    separated_string.back().pop_back();
                }
            }
        }
        else
        {
            for (int i = 0; i < input.length(); i++)
            {
                word += input[i];
                if (contain(word, separator))
                {
                    word.erase(word.find(separator), separator.length());
                    separated_string.push_back(word);
                    word.clear();
                }
            }
            separated_string.push_back(word);
        }
        return separated_string;
    }

    std::vector<int> remove(std::string input, char delimiter = ' ')
    {
        std::vector<int> tokens;

        std::istringstream ss(input);

        std::string each;
        while (std::getline(ss, each, delimiter))
        {
            if (!each.empty())
            {
                tokens.push_back(std::stoi(each));
            }
        }

        // for (std::string each; std::getline(ss, each, delimiter); tokens.push_back(std::stoi(each)));

        return tokens;
    }
}

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_04\\input.txt");
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
    std::vector<std::string> game_id;
    std::vector<int> win_num;
    std::vector<int> my_num;

    for (int i = 0; i < lines.size(); i++)
    {
        game_id.push_back(tools::separator(lines[i], ":")[1]);

        for (int j = 0; j < game_id.size(); j++)
        {
            auto temp = tools::separator(game_id[j], "|");

            win_num = tools::remove(temp[0], ' ');
            my_num = tools::remove(temp[1], ' ');

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
        game_id.clear();
    }

    return std::accumulate(result.begin(), result.end(), 0);
}

std::string part_two()
{
    return "0";
}

int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    int p1 = part_one();
    std::string p2 = part_two();

    std::cout << "Part One: " << p1 << std::endl;
    std::cout << "Part Two: " << p2 << std::endl;

    auto stop = high_resolution_clock::now();
    auto dura = duration_cast<milliseconds>(stop - start);
    std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

    return 0;
}
