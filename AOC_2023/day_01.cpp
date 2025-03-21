#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <chrono>

std::vector<std::string> read_file(const std::string& file_name)
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

std::string solve()
{
	std::vector<std::string> lines = read_file("input.txt");

	if (lines.empty())
	{
		return {};
	}

	std::vector<int> result;

	for (const std::string& line : lines)
	{
		char first_digit = '\0', last_digit = '\0';

		for (const char& c : line)
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

int main()
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	auto start = high_resolution_clock::now();

	std::string result = solve();

	std::cout << "Result: " << result << std::endl;

	auto stop = high_resolution_clock::now();
	auto dura = duration_cast<milliseconds>(stop - start);
	std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

	return 0;
}
