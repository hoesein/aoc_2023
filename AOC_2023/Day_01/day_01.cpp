#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <chrono>
#include <unordered_map>
#include <map>

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

std::string part_one()
{
	std::vector<std::string> lines = read_file("input.txt");

	if (lines.empty())
	{
		return {};
	}

	std::vector<int> result;

	for (const std::string &line : lines)
	{
		char first_digit = '\0', last_digit = '\0';

		for (const char &c : line)
		{
			if (isdigit(c))
			{
				if (!first_digit)
					first_digit = c;
				last_digit = c;
			}
		}

		if (first_digit)
		{
			int number = (first_digit == last_digit)
							 ? (first_digit - '0') * 11
							 : (first_digit - '0') * 10 + (last_digit - '0');
			result.push_back(number);
		}
	}

	int sum = std::accumulate(result.begin(), result.end(), 0);

	return std::to_string(sum);
}

std::string part_two()
{
	std::vector<std::string> lines = read_file("input.txt");
	if (lines.empty())
	{
		return {};
	}

	std::unordered_map<std::string, int> window_map = {
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9},
		{"1", 1},
		{"2", 2},
		{"3", 3},
		{"4", 4},
		{"5", 5},
		{"6", 6},
		{"7", 7},
		{"8", 8},
		{"9", 9}};
	std::vector<int> result;

	for (int i = 0; i < lines.size(); i++)
	{
		char first_digit = '\0', last_digit = '\0';
		std::vector<int> num_in_line;

		for (int w_start = 0; w_start < lines[i].size(); w_start++)
		{
			for (int w_end = w_start; w_end < lines[i].size(); w_end++)
			{
				std::string window = lines[i].substr(w_start, w_end - w_start + 1);
				if (window_map.find(window) != window_map.end())
				{
					num_in_line.push_back(window_map[window]);
				}
			}
		}

		if (num_in_line.size() == 1)
		{
			result.push_back(num_in_line[0] * 11);
		}
		else
		{
			result.push_back(num_in_line[0] * 10 + num_in_line[num_in_line.size() - 1]);
		}
	}
	return std::to_string(std::accumulate(result.begin(), result.end(), 0));
}

std::string approch_two()
{
	std::vector<std::string> lines = read_file("input.txt");
	if (lines.empty())
	{
		return {};
	}

	const std::unordered_map<std::string, int> window_map = {
		{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}};

	std::vector<int> result;
	for (const std::string &line : lines)
	{
		int fist = 0, last = 0;
		// Find first digit
		for (size_t i = 0; i < line.size(); ++i)
		{
			bool found = false;
			for (int len : {5, 4, 3, 1})
			{
				if (i + len > line.size())
					continue;
				auto substr = line.substr(i, len);
				auto it = window_map.find(substr);
				if (it != window_map.end())
				{
					if (fist == 0)
					{
						fist = it->second;
					}
					found = true;
					break;
				}
			}
			if (found)
				break;
		}

		// Find last digit
		for (size_t i = static_cast<int>(line.size()) - 1; i >= 0; --i)
		{
			bool found = false;
			for (int len : {5, 4, 3, 1})
			{
				if (i + len > line.size())
					continue;
				auto substr = line.substr(i, len);
				auto it = window_map.find(substr);
				if (it != window_map.end())
				{
					if (last == 0)
					{
						last = it->second;
					}
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		result.push_back(fist == last ? fist * 11 : fist * 10 + last);
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
	std::string p2 = approch_two();

	std::cout << "Part One: " << p1 << std::endl;
	std::cout << "Part Two: " << p2 << std::endl;

	auto stop = high_resolution_clock::now();
	auto dura = duration_cast<milliseconds>(stop - start);
	std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

	return 0;
}
