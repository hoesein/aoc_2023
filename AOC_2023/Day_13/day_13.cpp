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

int find_vertical(const std::vector<std::string> &pattern)
{
    std::cout << "\nChecking vertical mirros .." << std::endl;

    for(size_t col = 1; col < pattern[0].size(); col++)
    {
        bool reflact = true;
        std::cout << "Testing mirror between column " << col - 1 << " and " << col << std::endl;
        for(size_t i = 0; i < pattern.size(); i++)
        {
            for(size_t j = 0; j < std::min(col, pattern[0].size() - col); j++)
            {
                size_t left_col = col - 1 - j;
                size_t right_col = col + j;
                std::cout << " Row " << i << ": Comparing [" << i << "][" << left_col << "] (" << pattern[i][left_col] << ") with [" << i << "][" << right_col << "](" << pattern[i][right_col] << "): ";
                if(pattern[i][left_col] != pattern[i][right_col])
                {
                    std::cout << "MISMATCH" << std::endl;
                    reflact = false;
                    break;
                }
                std::cout << "MATCH" << std::endl;
            }
            if(!reflact) break;
        }
        if (reflact)
        {
            std::cout << "VALID MIRROR FOUND AT COLUMN " << col << std::endl;
            return col;
        }
    }    
    std::cout << "No vertical mirror found" << std::endl;
    return 0;
}

int find_horizontal(const std::vector<std::string> &pattern)
{
    for(size_t row = 1; row < pattern.size(); row++)
    {
        int is_mirror = true;
        for(size_t i = 0; i < std::min(row, pattern.size() - row); i++)
        {
            if(pattern[row - 1 - i] != pattern[row + i])
            {
                is_mirror = false;
                break;
            }
        }
        if(is_mirror) return row;
    }
    return 0;
}

int process_pattern(std::vector<std::string> pattern)
{
    int vertical = find_vertical(pattern);
    if(vertical > 0) return vertical;
    return 100 * find_horizontal(pattern);
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::vector<std::string>> groups;
    std::vector<std::string> block;
    int aa = lines.size();
    for(size_t i = 0; i < lines.size(); ++i)
    {
        if(lines[i].empty())
        {
            groups.push_back(block);
            block.clear();
        }
        else
        {
            block.push_back(lines[i]);
        }
        if (i == lines.size() - 1)
            groups.push_back(block);
    }
    
    int result = 0;
    for(const auto& pattern: groups)
    {
        result += process_pattern(pattern);
    }
    
    return std::to_string(result);
}

int find_vertical_with_smudge(const std::vector<std::string> &pattern)
{
    for(size_t col = 1; col < pattern[0].size(); col++)
    {
        int diff = 0;
        for(size_t i = 0; i < pattern.size(); i++)
        {
            for(size_t j = 0; j < std::min(col, pattern[0].size() - col); j++)
            {
                size_t left_col = col - 1 - j;
                size_t right_col = col + j;
                if(pattern[i][left_col] != pattern[i][right_col])
                {
                    diff++;
                    if (diff > 1)
                        break;
                }
            }
            if (diff > 1)
                break;
        }
        if (diff == 1)
            return col;
    }    
    return 0;
}

int find_horizontal_with_smudge(const std::vector<std::string> &pattern)
{
    for(size_t row = 1; row < pattern.size(); row++)
    {
        int diff = 0;
        for(size_t i = 0; i < std::min(row, pattern.size() - row); i++)
        {
            for(size_t j = 0; j < pattern[0].size(); j++)
            {
                if(pattern[row - 1 - i][j] != pattern[row + i][j])
                {
                    diff++;
                    if (diff > 1)
                    break;
                }
            }
            if (diff > 1)
                break;
        }
        if (diff == 1)
            return row;
    }
    return 0;
}

int process_pattern_for_smudge(std::vector<std::string> pattern)
{
    int vertical = find_vertical_with_smudge(pattern);
    if(vertical > 0) return vertical;
    return 100 * find_horizontal_with_smudge(pattern);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::vector<std::string>> groups;
    std::vector<std::string> block;
    int aa = lines.size();
    for(size_t i = 0; i < lines.size(); ++i)
    {
        if(lines[i].empty())
        {
            groups.push_back(block);
            block.clear();
        }
        else
        {
            block.push_back(lines[i]);
        }
        if (i == lines.size() - 1)
            groups.push_back(block);
    }
    
    int result = 0;
    for(const auto& pattern: groups)
    {
        result += process_pattern_for_smudge(pattern);
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
