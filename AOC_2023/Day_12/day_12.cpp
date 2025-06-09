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

std::unordered_map<std::string, long long> memo;
long long count_arrange(const std::string& pattern, const std::vector<int> groups, int pattern_pos, int group_pos, int current_len)
{
    std::string key = std::to_string(pattern_pos) + "," + std::to_string(group_pos) + "," + std::to_string(current_len);

    if(memo.find(key) != memo.end())
    {
        return memo[key];
    }
    if(pattern_pos == pattern.size())
    {
        if ((group_pos == groups.size() && current_len == 0) ||
            (group_pos == groups.size() - 1 && current_len == groups[group_pos]))
        {
            return 1;
        }
        return 0;
    }
    
    long long arrangements = 0;
    char c = pattern[pattern_pos];

    if(c == '.' || c == '?')
    {
        if(current_len == 0)
        {
            arrangements += count_arrange(pattern, groups, pattern_pos + 1, group_pos, 0);
        }
        else if(group_pos < groups.size() && current_len == groups[group_pos])
        {
            arrangements += count_arrange(pattern, groups, pattern_pos + 1, group_pos + 1, 0);
        }
    }
    
    if(c == '#' || c == '?')
    {
        if(group_pos < groups.size() && current_len < groups[group_pos])
        {
            arrangements += count_arrange(pattern, groups, pattern_pos + 1, group_pos, current_len + 1);
        }
    }
    memo[key] = arrangements;
    return arrangements;
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    long long result = 0;
    std::vector<std::vector<int>> groups;
    std::vector<std::string> patterns;
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<std::string> split = tools::separator(lines[i], " ");
        patterns.push_back(split[0]);
        
        std::vector<int> temp_groups;
        for(int i: tools::remove<int>(split[1], ','))
        {
            temp_groups.push_back(i); 
        }
        result += count_arrange(split[0], temp_groups, 0, 0, 0);
        groups.push_back(temp_groups);
        memo.clear();
    }

    return std::to_string(result);
}

std::string unfold_pattern(const std::string& pattern)
{
    std::string unfold;
    for(size_t i = 0; i < 5; i++)
    {
        if(i != 0) unfold += "?";
        unfold += pattern;
    }
    return unfold;
}

std::vector<int> unfold_group(const std::vector<int>& group)
{
    std::vector<int> unfold;
    for(size_t i = 0; i < 5; i++)
    {
        unfold.insert(unfold.end(), group.begin(), group.end());
    }   
    return unfold;
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }
    
    long long result = 0;
    std::vector<std::vector<int>> groups;
    std::vector<std::string> patterns;
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<std::string> split = tools::separator(lines[i], " ");
        patterns.push_back(split[0]);
        
        std::vector<int> temp_groups;
        for(int i: tools::remove<int>(split[1], ','))
        {
            temp_groups.push_back(i); 
        }
        result += count_arrange(unfold_pattern(split[0]), unfold_group(temp_groups), 0, 0, 0);
        groups.push_back(temp_groups);
        memo.clear();
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
