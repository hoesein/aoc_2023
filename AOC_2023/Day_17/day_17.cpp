#include "../common.h"

// Dijkstra's algorithm implementation for pathfinding

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

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct State
{
    int row, col;
    Direction dir;
    int stpes_count;
    int heat_loss;

    bool operator>(const State &other) const
    {
        return heat_loss > other.heat_loss;
    }
};

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::vector<int>> grid;
    for (const auto line : lines)
    {
        std::vector<int> row;
        for (const auto ch : line)
        {
            row.push_back(ch - '0');
        }
        grid.push_back(row);
    }

    int num_rows = grid.size();
    int num_cols = grid[0].size();

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    // Key: tuple<row, col, direction, steps_in_same_direction>
    std::map<std::tuple<int, int, Direction, int>, int> min_heat;
    pq.push({0, 0, RIGHT, 0, 0});
    pq.push({0, 0, DOWN, 0, 0});

    // Dijkstra's algorithm main loop
    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();
        int row = current.row;
        int col = current.col;
        Direction dir = current.dir;
        int steps = current.stpes_count;
        int heat_loss = current.heat_loss;

        // If we reach the bottom-right corner, return the heat loss
        if (row == num_rows - 1 && col == num_cols - 1)
        {
            return std::to_string(heat_loss);
        }

        // Skip if we have already found a better path to this state
        auto state_key = std::make_tuple(row, col, dir, steps);
        if (min_heat.count(state_key) && min_heat[state_key] <= heat_loss)
        {
            continue;
        }
        min_heat[state_key] = heat_loss;

        // Explore neighbors
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        std::vector<Direction> dir_enum = {UP, DOWN, LEFT, RIGHT};

        for (size_t i = 0; i < directions.size(); ++i)
        {
            int new_row = row + directions[i].first;
            int new_col = col + directions[i].second;
            Direction new_dir = dir_enum[i];

            if (new_row < 0 || new_row >= num_rows || new_col < 0 || new_col >= num_cols)
            {
                continue; // Skip out-of-bounds
            }

            int new_steps = (new_dir == dir) ? steps + 1 : 1;
            int new_heat_loss = heat_loss + grid[new_row][new_col] + (new_steps > 3 ? new_steps - 3 : 0);

            // Ensure no more than 3 steps in one direction
            if (new_steps > 3)
            {
                continue;
            }

            // Ensure not to move backward
            if ((dir == UP && new_dir == DOWN) ||
                (dir == DOWN && new_dir == UP) ||
                (dir == LEFT && new_dir == RIGHT) ||
                (dir == RIGHT && new_dir == LEFT))
            {
                continue;
            }

            pq.push({new_row, new_col, new_dir, new_steps, new_heat_loss});
        }
    }
    return "0";
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::vector<int>> grid;
    for (const auto line : lines)
    {
        std::vector<int> row;
        for (const auto ch : line)
        {
            row.push_back(ch - '0');
        }
        grid.push_back(row);
    }

    int num_rows = grid.size();
    int num_cols = grid[0].size();

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    // Key: tuple<row, col, direction, steps_in_same_direction>
    std::map<std::tuple<int, int, Direction, int>, int> min_heat;
    pq.push({0, 0, RIGHT, 0, 0});
    pq.push({0, 0, DOWN, 0, 0});

    // Dijkstra's algorithm main loop
    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();
        int row = current.row;
        int col = current.col;
        Direction dir = current.dir;
        int steps = current.stpes_count;
        int heat_loss = current.heat_loss;

        // If we reach the bottom-right corner, return the heat loss
        if (row == num_rows - 1 && col == num_cols - 1)
        {
            return std::to_string(heat_loss);
        }

        // Skip if we have already found a better path to this state
        auto state_key = std::make_tuple(row, col, dir, steps);
        if (min_heat.count(state_key) && min_heat[state_key] <= heat_loss)
        {
            continue;
        }
        min_heat[state_key] = heat_loss;

        // Explore neighbors
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        std::vector<Direction> dir_enum = {UP, DOWN, LEFT, RIGHT};

        for (size_t i = 0; i < directions.size(); ++i)
        {
            int new_row = row + directions[i].first;
            int new_col = col + directions[i].second;
            Direction new_dir = dir_enum[i];

            if (new_row < 0 || new_row >= num_rows || new_col < 0 || new_col >= num_cols)
            {
                continue; // Skip out-of-bounds
            }

            int new_steps = (new_dir == dir) ? steps + 1 : 1;
            if (new_steps > 10)
                continue;

            if (new_dir != dir && steps < 4)
            {
                continue;
            }

            int new_heat_loss = heat_loss + grid[new_row][new_col];

            // Ensure not to move backward
            if ((dir == UP && new_dir == DOWN) ||
                (dir == DOWN && new_dir == UP) ||
                (dir == LEFT && new_dir == RIGHT) ||
                (dir == RIGHT && new_dir == LEFT))
            {
                continue;
            }

            pq.push({new_row, new_col, new_dir, new_steps, new_heat_loss});
        }
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
