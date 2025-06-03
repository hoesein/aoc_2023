#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_11\\input.txt");
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

struct Galaxy
{
    int row;
    int col;
};

int get_dist(const Galaxy& ga, const Galaxy& gb, const std::vector<bool>& rowIsEmpty, const std::vector<bool>& colIsEmpty)
{
    int dr = std::abs(ga.row - gb.row);
    int dc = std::abs(ga.col - gb.col);

    int dist = dr + dc;
    for(int i = std::min(ga.row, gb.row) + 1; i < std::max(ga.row, gb.row); i++)
    {
        dist += rowIsEmpty[i] ? 1 : 0;
    }
    
    for(int j = std::min(ga.col, gb.col) + 1; j < std::max(ga.col, gb.col); j++)
    {
        dist += colIsEmpty[j] ? 1 : 0;
    }
    return dist;
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cout << "No data found." << std::endl;
        return 0;
    }
    
    std::vector<bool> rowIsEmpty(lines.size(), true);
    std::vector<bool> colIsEmpty(lines[0].size(), true);
    
    std::vector<Galaxy> galaxies;

    for(size_t i = 0; i < lines.size(); i++)
    {
        for(size_t j = 0; j < lines[0].size(); j++)
        {
            if(lines[i][j] == '#')
            {
                rowIsEmpty[i] = false;
                colIsEmpty[j] = false;

                Galaxy galaxy = {static_cast<int>(i), static_cast<int>(j)};
                galaxies.push_back(galaxy);
            }
        }
    }

    size_t ans = 0;
    for(size_t rIdx = 0; rIdx < galaxies.size(); rIdx++)
    {
        for(size_t cIdx = rIdx + 1; cIdx < galaxies.size(); cIdx++)
        {
            const auto& ga = galaxies[rIdx];
            const auto& gb = galaxies[cIdx];

            int dist = get_dist(ga, gb, rowIsEmpty, colIsEmpty);

            ans += dist;
        }
    }

    return std::to_string(ans);
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
