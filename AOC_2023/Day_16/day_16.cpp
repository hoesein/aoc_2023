#include "../common.h"

// Breadth-First Search (BFS) implementation to solve the problem of energizing beams in a grid with mirrors.

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_16\\input.txt");
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

enum Direction { UP, DOWN, LEFT, RIGHT };

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

struct Beam
{
    int row, col;
    Direction dir;

    Beam(int r, int c, Direction d) : row(r), col(c), dir(d) {}

    void move()
    {
        row += dr[dir];
        col += dc[dir];
    }

    bool operator<(const Beam& other) const
    {
        return std::tie(row, col, dir) < std::tie(other.row, other.col, other.dir);
    }
};

Direction reflect(Direction current, char mirror)
{
    switch (mirror)
    {
        case '/':
            return (current == UP) ? RIGHT : (current == RIGHT) ? UP : (current == DOWN) ? LEFT : DOWN;
        case '\\':
            return (current == UP) ? LEFT : (current == LEFT) ? UP : (current == DOWN) ? RIGHT : DOWN;
        default:
            return current; // No reflection
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

    int rows = lines.size();
    int cols = lines[0].size();

    std::vector<std::vector<bool>> energized(rows, std::vector<bool>(cols, false));
    std::set<Beam> visited;
    std::queue<Beam> queue;
    queue.push(Beam(0, 0, RIGHT));

    while (!queue.empty())
    {
        Beam current = queue.front();
        queue.pop();

        if (current.row < 0 || current.row >= rows ||   // if row is lower than 0 or greater than rows length
            current.col < 0 || current.col >= cols)     // if column is lower than 0 or greater than columns length
        {
            continue; // out of bounds
        }

        if(visited.count(current)) // if beam has been found in visited beam list, skip to prevent cycling loop
        {
            continue;
        }

        energized[current.row][current.col] = true;  // mark current position as energized
        visited.insert(current);                     // add current beam to visited list                

        char cell = lines[current.row][current.col]; // get current cell char to handle direction and reflection
        std::vector<Direction> new_dir;
        switch(cell)
        {
            case '.':
                new_dir.push_back(current.dir);
                break;
            case '/':
                new_dir.push_back(reflect(current.dir, cell));
                break;
            case '\\':
                new_dir.push_back(reflect(current.dir, cell));
                break;
            case '|':
                if(current.dir == LEFT || current.dir == RIGHT)
                {
                    new_dir.push_back(UP);
                    new_dir.push_back(DOWN);
                }
                else
                {
                    new_dir.push_back(current.dir);
                }
                break;
            case '-':
                if(current.dir == UP || current.dir == DOWN)
                {
                    new_dir.push_back(LEFT);
                    new_dir.push_back(RIGHT);
                }
                else
                {
                    new_dir.push_back(current.dir);
                }             
                break;
        }
        for(Direction d: new_dir)
        {
            Beam new_beam = current;
            new_beam.dir = d;       // set new beam direction
            new_beam.move();        // move the beam to the next position
            queue.push(new_beam);   // add new beam to the queue
        }
    }
    
    int total = 0;
    for(const auto& energize: energized)
    {
        total += std::count_if(energize.begin(), energize.end(),
                               [](bool e) { return e; });
    }
    
    return std::to_string(total);
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
