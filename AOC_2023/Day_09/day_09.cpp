#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("test.txt");
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
        return 0;
    }

    int result = 0;
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<int> current_row = tools::remove<int>(lines[i], ' ');
        
        // create diff map for current row
        std::vector<std::vector<int>> diff_row = {current_row};

        while (!std::all_of(diff_row.back().begin(), diff_row.back().end(),
                            [](int num) { return num == 0; }))
        {
            const auto& last_diff = diff_row.back();
            std::vector<int> new_diff;

            for (size_t j = 0; j < last_diff.size() - 1; j++)
            {
                int diff = last_diff[j + 1] - last_diff[j];
                new_diff.push_back(diff);
            }

            diff_row.push_back(new_diff);
        }

        int extpo_value = 0;
        for(auto it = diff_row.rbegin(); it != diff_row.rend(); it++)
        {
           extpo_value += it->back(); 
        }
        result += extpo_value;
    }
    
    return std::to_string(result);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No Data found." << std::endl;
        return 0;
    }

    int result = 0;
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<int> current_row = tools::remove<int>(lines[i], ' ');
        
        // create diff map for current row
        std::vector<std::vector<int>> diff_row = {current_row};

        while (!std::all_of(diff_row.back().begin(), diff_row.back().end(),
                            [](int num) { return num == 0; }))
        {
            const auto& last_diff = diff_row.back();
            std::vector<int> new_diff;

            for (size_t j = 0; j < last_diff.size() - 1; j++)
            {
                int diff = last_diff[j + 1] - last_diff[j];
                new_diff.push_back(diff);
            }

            diff_row.push_back(new_diff);
        }

        int extpo_value = 0;
        for(auto it = diff_row.rbegin(); it != diff_row.rend(); it++)
        {
            extpo_value = it->front() - extpo_value;
        }
        result += extpo_value;
    }
    
    return std::to_string(result);
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
