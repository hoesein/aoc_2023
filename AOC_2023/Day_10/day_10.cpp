#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_10\\input.txt");
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

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }
    int sr, sc;
    for(size_t i = 0; i < lines.size(); i++)
    {
        bool lb = false;
        for(size_t j = 0; j < lines[i].size(); j++)
        {
            if(lines[i][j] == 'S')
            {
                sr = i;
                sc = j;
                lb = true;
                break;
            }
            if(lb) break;
        }
    }
    std::set<std::pair<int, int>> seen;
    seen.insert(std::make_pair(sr, sc));

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(sr, sc));
    
    while (!q.empty())
    {
        std::pair<int, int> curr_pos = q.front();
        q.pop();
        int r = curr_pos.first;
        int c = curr_pos.second;
        char curr_ch = lines[r][c];

        // check previous row
        auto &prch = lines[r - 1][c];
        if (r > 0 && (curr_ch == 'S' || curr_ch == 'L' || curr_ch == 'J' || curr_ch == '|') && (lines[r - 1][c] == '|' || lines[r - 1][c] == '7' || lines[r - 1][c] == 'F') && seen.find(std::make_pair(r - 1, c)) == seen.end())
        {
            seen.insert(std::make_pair(r - 1, c));
            q.push(std::make_pair(r - 1, c));
        }

        // check next row
        auto &nrch = lines[r + 1][c];
        if (r < lines.size() && (curr_ch == 'S' || curr_ch == '|' || curr_ch == '7' || curr_ch == 'F') && (lines[r + 1][c] == '|' || lines[r + 1][c] == 'J' || lines[r + 1][c] == 'L') && seen.find(std::make_pair(r + 1, c)) == seen.end())
        {
            seen.insert(std::make_pair(r + 1, c));
            q.push(std::make_pair(r + 1, c));
        }

        // check left column
        auto &lcch = lines[r][c - 1];
        if (c > 0 && (curr_ch == 'S' || curr_ch == '-' || curr_ch == 'J' || curr_ch == '7') && (lines[r][c - 1] == '-' || lines[r][c - 1] == 'L' || lines[r][c - 1] == 'F') && seen.find(std::make_pair(r, c - 1)) == seen.end())
        {
            seen.insert(std::make_pair(r, c - 1));
            q.push(std::make_pair(r, c - 1));
        }
        
        // check right column
        auto &rcch = lines[r][c + 1];
        if (c < lines[r].size() && (curr_ch == 'S' || curr_ch == '-' || curr_ch == 'L' || curr_ch == 'F') && (lines[r][c + 1] == '-' || lines[r][c + 1] == 'J' || lines[r][c + 1] == '7') && seen.find(std::make_pair(r, c + 1)) == seen.end())
        {
            seen.insert(std::make_pair(r, c + 1));
            q.push(std::make_pair(r, c + 1));
        } 
    }

    // for (const auto &s : seen)
    // {
    //     std::cout << s.first << " and " << s.second << std::endl;
    // }

    return std::to_string(seen.size()/2);
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

	std::string p1 = part_one();
	std::string p2 = part_two();

	std::cout << "Part One: " << p1 << std::endl;
	std::cout << "Part Two: " << p2 << std::endl;

	auto stop = high_resolution_clock::now();
	auto dura = duration_cast<milliseconds>(stop - start);
	std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

	return 0;
}
