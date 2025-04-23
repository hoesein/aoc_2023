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
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
    }

    // get instruction data
    std::vector<int> instruction;
    for(int i = 0; i < lines[0].size(); i++)
    {
        if(lines[0][i] == 'R')
        {
            instruction.push_back(1);
        }
        if(lines[0][i] == 'L')
        {
            instruction.push_back(0);
        }
    }

    std::map<std::string, std::vector<std::string>> node_map;
    for(int i = 2; i < lines.size(); i++)
    {
        std::string source = tools::separator(lines[i], "=")[0];
        std::string right = tools::separator(lines[i], "=")[1];
        std::vector<std::string> data = tools::separator(right, ",");
        tools::trim(source);
        tools::trim(data[0]);
        tools::trim(data[1]);
        node_map[source] = data;
    }

    std::string start_node = "AAA";
    int step = 0;
    size_t index = 0;
    while(start_node != "ZZZ")
    {
        start_node = node_map[start_node][instruction[index]];
        // if(start_node == "ZZZ") break;
        step++;
        index = (index + 1) % instruction.size();
    }

    return std::to_string(step);
}

// function to calculate greatest common divisor
long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// function to calculate least common multiple
long long lcm(long long a, long long b)
{
    return (a / gcd(a, b)) * b;    
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
    }

    // get instruction data
    std::vector<int> instruction;
    for(int i = 0; i < lines[0].size(); i++)
    {
        if(lines[0][i] == 'R')
        {
            instruction.push_back(1);
        }
        if(lines[0][i] == 'L')
        {
            instruction.push_back(0);
        }
    }

    std::map<std::string, std::vector<std::string>> node_map;
    for(int i = 2; i < lines.size(); i++)
    {
        std::string source = tools::separator(lines[i], "=")[0];
        std::string right = tools::separator(lines[i], "=")[1];
        std::vector<std::string> data = tools::separator(right, ",");
        tools::trim(source);
        tools::trim(data[0]);
        tools::trim(data[1]);
        node_map[source] = data;
    }

    std::vector<std::string> current_node;
    for(const auto& node: node_map)
    {
        if(node.first.back() == 'A')
        {
            current_node.push_back(node.first);
        }
    }

    std::vector<long long> cycle_length;
    for (const auto &node : current_node)
    {
        long long steps = 0;
        std::string current = node;
        size_t current_index = 0;
        while (current.back() != 'Z')
        {
            current = node_map[current][instruction[current_index]];
            steps++;
            current_index = (current_index + 1) % instruction.size();
        }
        cycle_length.push_back(steps);
    }

    // compute total step from cycle lenght
    long long total_step = cycle_length[0];
    for(size_t i = 0; i < cycle_length.size(); i++)
    {
        total_step = lcm(total_step, cycle_length[i]);
    }

    return std::to_string(total_step);
}

int main()
{
    using std::chrono::duration;
	using std::chrono::duration_cast;
	using std::chrono::high_resolution_clock;
	using std::chrono::milliseconds;

	auto start = high_resolution_clock::now();

	// std::string p1 = part_one();
	std::string p2 = part_two();

	// std::cout << "Part One: " << p1 << std::endl;
	std::cout << "Part Two: " << p2 << std::endl;

	auto stop = high_resolution_clock::now();
	auto dura = duration_cast<milliseconds>(stop - start);
	std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

	return 0;
}
