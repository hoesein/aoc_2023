#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <numeric>
#include <map>

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_03\\input.txt");
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

bool is_symbols(const char &ch)
{
    return ch != '.' && !isdigit(ch);
}

std::string part_one()
{
    std::vector<long> result;
    std::vector<std::string> input = read_file();
    std::vector<std::vector<char>> grid;
    for (int i = 0; i < input.size(); i++)
    {
        std::vector<char> line;
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '\n')
                continue;
            line.push_back(input[i][j]);
        }
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<int> row_direction = {-1, 0, 1};
    std::vector<int> col_direction = {-1, 0, 1};

    for (int row = 0; row < rows; ++row)
    {
        int num_str = 0;
        for (int col = 0; col < cols;)
        {
            if (isdigit(grid[row][col]))
            {
                // grab the whole number
                int start = col;
                int end = 0;
                while (col < cols && isdigit(grid[row][col]))
                {
                    num_str = num_str * 10 + grid[row][col] - '0';
                    end = ++col;
                }
                std::cout << "Found number: " << num_str << " at (" << row << "," << start << ")-(" << row << "," << col - 1 << ")" << std::endl;

                bool adjacent_symbol = false;
                // mark for current number position, start as start position and
                for (int k = start; k < end; ++k)
                {
                    // std::cout << "Checking digit at (" << row << "," << k << ")" << std::endl;
                    // loop trough for previous row/col and next row/col for searching symbol
                    for (int rd = -1; rd <= 1; ++rd)
                    {
                        for (int cd = -1; cd <= 1; ++cd)
                        {
                            if (rd == 0 && cd == 0)
                                continue;
                            int nr = row + rd;
                            int nc = k + cd;
                            // std::cout << "position [" << nr << ", " << nc << "]" << std::endl;
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
                            {
                                // std::cout << "position [" << nr << ", " << nc << "] => " << grid[nr][nc] << std::endl;
                                if (is_symbols(grid[nr][nc]))
                                {
                                    adjacent_symbol = true;
                                    break;
                                }
                            }
                            if (adjacent_symbol)
                                break;
                        }
                        if (adjacent_symbol)
                            break;
                    }
                    if (adjacent_symbol)
                        break;
                }

                if (adjacent_symbol)
                {
                    result.push_back(num_str);
                }
                num_str = 0;
            }
            else
            {
                ++col;
            }
        }
    }
    return std::to_string(std::accumulate(result.begin(), result.end(), 0));
}

std::string part_two()
{
    std::vector<long> result;
    std::vector<std::string> input = read_file();
    std::vector<std::vector<char>> grid;
    for (int i = 0; i < input.size(); i++)
    {
        std::vector<char> line;
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '\n')
                continue;
            line.push_back(input[i][j]);
        }
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<int> row_direction = {-1, 0, 1};
    std::vector<int> col_direction = {-1, 0, 1};

    std::map<std::vector<int>, std::vector<int>> gears;

    for (int row = 0; row < rows; ++row)
    {
        int num_str = 0;
        for (int col = 0; col < cols;)
        {
            if (isdigit(grid[row][col]))
            {
                // grab the whole number
                int start = col;
                int end = 0;
                while (col < cols && isdigit(grid[row][col]))
                {
                    num_str = num_str * 10 + grid[row][col] - '0';
                    end = ++col;
                }
                std::cout << "Found number: " << num_str << " at (" << row << "," << start << ")-(" << row << "," << col - 1 << ")" << std::endl;

                bool adjacent_symbol = false;
                std::vector<int> found_gear;
                // mark for current number position, start as start position and
                for (int k = start; k < end; ++k)
                {
                    // std::cout << "Checking digit at (" << row << "," << k << ")" << std::endl;
                    // loop trough for previous row/col and next row/col for searching symbol
                    for (int rd = -1; rd <= 1; ++rd)
                    {
                        for (int cd = -1; cd <= 1; ++cd)
                        {
                            if (rd == 0 && cd == 0)
                                continue;
                            int nr = row + rd;
                            int nc = k + cd;
                            // std::cout << "position [" << nr << ", " << nc << "]" << std::endl;
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
                            {
                                // std::cout << "position [" << nr << ", " << nc << "] => " << grid[nr][nc] << std::endl;
                                if (grid[nr][nc] == '*')
                                {
                                    gears[{nr, nc}];
                                    found_gear.push_back(nr);
                                    found_gear.push_back(nc);
                                    adjacent_symbol = true;
                                    break;
                                }
                            }
                            if (adjacent_symbol)
                                break;
                        }
                        if (adjacent_symbol)
                            break;
                    }
                    if (adjacent_symbol)
                        break;
                }

                if (adjacent_symbol)
                {
                    gears[found_gear].push_back(num_str);
                    found_gear.clear();
                    // result.push_back(num_str);
                }
                num_str = 0;
            }
            else
            {
                ++col;
            }
        }
    }

    for(const auto& gear: gears)
    {
        if(gear.second.size() == 2){
            result.push_back(gear.second[0] * gear.second[1]);
        }
    }

    return std::to_string(std::accumulate(result.begin(), result.end(), 0));
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
