#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <array>
#include <numeric>

std::vector<std::string> read_file(const std::string &file_name)
{
    std::ifstream input_file(file_name);
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
    enum COLOR
    {
        RED,
        GREEN,
        BLUE,
        COUNT
    };

    std::array<int, COUNT> max_color_count = {12, 13, 14};

    std::vector<std::string> lines = read_file("input.txt");
    if (lines.empty())
    {
        std::cerr << "File is empty." << std::endl;
        return {};
    }

    std::vector<int> result;
    int game_id = 0;
    for (const std::string &line : lines)
    {
        ++game_id;
        bool possiable_game = false;
        int current_color_count = 0;
        size_t pos = line.find(":");
        for (size_t i = pos + 2; i < line.size(); ++i)
        {
            char color = line[i];
            if (color == ' ')
                continue;
            if (std::isdigit(color))
            {
                if (std::isdigit(line[i + 1]))
                {
                    current_color_count += (color - '0') * 10 + (line[i + 1] - '0');
                    i += 1;
                    continue;
                }
                else
                {
                    current_color_count += color - '0';
                    continue;
                }
            }

            COLOR c;
            switch (color)
            {
            case 'r':
                i += 4;
                c = RED;
                break;
            case 'g':
                i += 6;
                c = GREEN;
                break;
            case 'b':
                i += 5;
                c = BLUE;
                break;
            default:
                break;
            }

            if (current_color_count > max_color_count[c])
            {
                possiable_game = false;
                break;
            }

            current_color_count = 0;
            possiable_game = true;
        }
        if (possiable_game)
            result.push_back(game_id);
    }

    return std::accumulate(result.begin(), result.end(), 0);
}

int part_two()
{
    enum COLOR
    {
        RED,
        GREEN,
        BLUE,
        COUNT
    };

    std::array<int, COUNT> max_color_count = {12, 13, 14};

    std::vector<std::string> lines = read_file("input.txt");
    if (lines.empty())
    {
        std::cerr << "File is empty." << std::endl;
        return {};
    }

    std::vector<int> result;
    int game_id = 0;
    for (const std::string &line : lines)
    {
        ++game_id;
        bool possiable_game = false;
        int current_color_count = 0;
        size_t pos = line.find(":");
        for (size_t i = pos + 2; i < line.size(); ++i)
        {
            char color = line[i];
            if (color == ' ')
                continue;
            if (std::isdigit(color))
            {
                if (std::isdigit(line[i + 1]))
                {
                    current_color_count += (color - '0') * 10 + (line[i + 1] - '0');
                    i += 1;
                    continue;
                }
                else
                {
                    current_color_count += color - '0';
                    continue;
                }
            }

            COLOR c;
            switch (color)
            {
            case 'r':
                i += 4;
                c = RED;
                break;
            case 'g':
                i += 6;
                c = GREEN;
                break;
            case 'b':
                i += 5;
                c = BLUE;
                break;
            default:
                break;
            }

            if (current_color_count > max_color_count[c])
            {
                possiable_game = false;
                break;
            }

            current_color_count = 0;
            possiable_game = true;
        }
        if (possiable_game)
            result.push_back(game_id);
    }

    return std::accumulate(result.begin(), result.end(), 0);
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