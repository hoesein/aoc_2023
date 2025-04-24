#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_09\\input.txt");
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
    if (lines.empty())
    {
        std::cerr << "No Data found." << std::endl;
    }

    int result = 0;
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<int> current_row = tools::remove<int>(lines[i], ' ');
        
        // create diff map for current row
        std::vector<std::vector<int>> diff_row;
        diff_row.push_back(current_row);
        int curr_lst = 0;

        while (true)
        {
            std::vector<int> current_list;
            for (size_t j = 0; j < diff_row[curr_lst].size() - 1; j++)
            {
                int diff = diff_row[curr_lst][j + 1] - diff_row[curr_lst][j];
                current_list.push_back(diff);
            }

            diff_row.push_back(current_list);
            curr_lst += 1;

            if (std::accumulate(current_list.begin(), current_list.end(), 0) == 0)
                break;
        }

        for(size_t k = 0; k < diff_row.size(); k++)
        {
            result += diff_row[k][diff_row[k].size() - 1]; 
        }
    }
    
    return std::to_string(result);
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
