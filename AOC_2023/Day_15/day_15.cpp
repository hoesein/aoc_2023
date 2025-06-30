#include "../common.h"

/*
    * set current value to 0
    * change first letter of char to ASCII value
    * then multiply by 17
    * then get remainder of divided by 256
*/

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_15\\input.txt");
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

    std::vector<std::string> separated_lines;
    for (const auto& line : lines)
    {
        auto separated = tools::separator(line, ",");
        separated_lines.insert(separated_lines.end(), separated.begin(), separated.end());
    }

    int result = 0;
    for(const auto& separated_line : separated_lines)
    {
        std::string word = separated_line;
        tools::trim(word);
        if (word.empty())
            continue;

        int value = 0;
        for (char c : word)
        {
            value += static_cast<int>(c);
            value *= 17;
            value %= 256;
        }

        // std::cout << "Value for '" << word << "': " << value << std::endl;
        result += value;
    }

    return std::to_string(result);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }
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
