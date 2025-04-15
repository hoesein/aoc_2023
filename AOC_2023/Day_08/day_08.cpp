#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

std::vector<std::string> read_file()
{
    std::ifstream input_file("input.txt");
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
    return "0";
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
