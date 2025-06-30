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

void tilt_north(std::vector<std::string> &platforms)
{
    for(size_t col = 0; col < platforms[0].size(); col++)
    {
        int empty_row = 0;
        for(size_t row = 0; row < platforms.size(); row++)
        {
            if(platforms[row][col] == 'O')
            {
                if(row != empty_row)
                {
                    platforms[empty_row][col] = 'O';
                    platforms[row][col] = '.';
                }
                empty_row++;
            }else if(platforms[row][col] == '#')
            {
                empty_row = row + 1;
            }
        }
    }
}

void tilt_west(std::vector<std::string> &platforms)
{
    for(size_t row = 0; row < platforms.size(); row++)
    {
        int empty_col = 0;
        for(size_t col = 0; col < platforms[row].size(); col++)
        {
            if(platforms[row][col] == 'O')
            {
                if(col != empty_col)
                {
                    platforms[row][empty_col] = 'O';
                    platforms[row][col] = '.';
                }
                empty_col++;
            }else if(platforms[row][col] == '#')
            {
                empty_col = col + 1;
            }
        }
    }
}

void tilt_south(std::vector<std::string> &platforms)
{
    for(size_t col = 0; col < platforms[0].size(); col++)
    {
        int empty_row = platforms.size() - 1;
        for(int row = platforms.size() - 1; row >= 0; row--)
        {
            if(platforms[row][col] == 'O')
            {
                if(row != empty_row)
                {
                    platforms[empty_row][col] = 'O';
                    platforms[row][col] = '.';
                }
                empty_row--;
            }else if(platforms[row][col] == '#')
            {
                empty_row = row - 1;
            }
        }
    }
}

void tilt_east(std::vector<std::string> &platforms)
{
    for(size_t row = 0; row < platforms.size(); row++)
    {
        int empty_col = platforms[row].size() - 1;
        for(int col = platforms[row].size() - 1; col >= 0; col--)
        {
            if(platforms[row][col] == 'O')
            {
                if(col != empty_col)
                {
                    platforms[row][empty_col] = 'O';
                    platforms[row][col] = '.';
                }
                empty_col--;
            }else if(platforms[row][col] == '#')
            {
                empty_col = col - 1;
            }
        }
    }
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }
    
    tilt_north(lines);
    
    int total = 0;
    for(size_t row = 0; row < lines.size(); row++)
    {
        int rock = std::count(lines[row].begin(), lines[row].end(), 'O');
        total += rock * (lines.size() - row);
    }

    return std::to_string(total);
}

void full_cycle(std::vector<std::string> &platforms)
{
    tilt_north(platforms);
    tilt_west(platforms);
    tilt_south(platforms);
    tilt_east(platforms);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::map<std::vector<std::string>, int> seen;
    int cycles = 1'000'000'000;
    for (int i = 0; i < cycles; i++)
    {
        full_cycle(lines);

        if (seen.count(lines))
        {
            int cycle_length = i - seen[lines];
            int remaining_cycles = (cycles - i - 1) % cycle_length;
            while(remaining_cycles--) full_cycle(lines);
            break;
        }
        seen[lines] = i;
    }

    int total = 0;
    for(size_t row = 0; row < lines.size(); row++)
    {
        int rock = std::count(lines[row].begin(), lines[row].end(), 'O');
        total += rock * (lines.size() - row);
    }

    return std::to_string(total);
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
    
	std::cout << "\nPart One: " << p1 << std::endl;
	std::cout << "Part Two: " << p2 << std::endl;

	auto stop = high_resolution_clock::now();
	auto dura = duration_cast<milliseconds>(stop - start);
	std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

	return 0;
}
