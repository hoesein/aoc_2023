#include "../common.h"

std::vector<std::string> read_file()
{
    std::ifstream input_file("input.txt");
    if (!input_file.is_open())
    {
        std::cerr << "Error opening file. " << std::endl;
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

struct Point
{
    long long row, column;
    
    Point(long long row = 0, long long column = 0) : row(row), column(column) {}
    
    Point operator+(const Point& other) const {
        return Point(row + other.row, column + other.column);
    }
    
    Point operator*(int scalar) const {
        return Point(row * scalar, column * scalar);
    }
};

struct DigPlan
{
    Point cube;
    int length;
    std::string color;

    DigPlan(Point cube, int length, std::string& color)
        : cube(cube), length(length), color(color) {}
};

std::map<std::string, Point> directions = {
    {"U", Point(-1, 0)},
    {"D", Point(1, 0)},
    {"L", Point(0, -1)},
    {"R", Point(0, 1)}
};

DigPlan parse_line(const std::string& line) {
    std::istringstream iss(line);
    std::string dir_str, color;
    int length;
    iss >> dir_str >> length >> color;

    if (directions.find(dir_str) == directions.end()) {
        throw std::invalid_argument("Invalid direction: " + dir_str);
    }

    return DigPlan(directions[dir_str], length, color);
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return "Error";
    }

    // prepare to digging the trenches
    std::vector<DigPlan> plans;
    for (const auto& line : lines)
    {
        plans.push_back(parse_line(line));
    }

    // start digging the trenches
    Point current_pos(0, 0);
    std::vector<Point> trenches = {current_pos};
    long long boundary_point = 0;

    for (const auto& plan : plans)
    {
        // * operator overload in Point struct
        Point motion = plan.cube * plan.length;
        // + operator overload in Point struct
        current_pos = current_pos + motion;
        trenches.push_back(current_pos);
        boundary_point += plan.length;
    }

    // calculate the area using the shoelace formula
    int shoelace_sum = 0;
    int n = trenches.size();
    for (int i = 0; i < n; i++)
    {
        const Point& a = trenches[i]; // get current point
        const Point& b = trenches[(i + 1) % n]; // get next point and loop back to the start
        shoelace_sum += a.row * b.column - a.column * b.row;
    }

    // apply Pick's Theorem to find the number of interior points
    int area = std::abs(shoelace_sum);
    int result = (area + boundary_point) / 2 + 1;
    return std::to_string(result);
}

std::map<char, Point> two_directions = {
    {'0', Point(0, 1)},
    {'1', Point(1, 0)},
    {'2', Point(0, -1)},
    {'3', Point(-1, 0)}
};

DigPlan parse_line_two(const std::string& line)
{
    std::istringstream iss(line);
    std::string dir_str, color;
    long long length;
    iss >> dir_str >> length >> color;
    std::string haxcode = color.substr(2, 5);
    char dir_char = color[7];

    if (two_directions.find(dir_char) == two_directions.end()) {
        throw std::invalid_argument("Invalid direction: " + std::string(1, dir_char));
    }

    length = std::stoll(haxcode, nullptr, 16); // hex -> decimal

    return DigPlan(two_directions[dir_char], length, color);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if(lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    // prepare to digging the trenches
    std::vector<DigPlan> plans;
    for(const auto& line: lines)
    {
        plans.push_back(parse_line_two(line));
    }
    
    // start digging the trenches
    Point current_pos(0, 0);
    std::vector<Point> trenches = {current_pos};
    long long boundary_point = 0;
    for(const auto& plan: plans)
    {
        Point motion = plan.cube * plan.length;
        current_pos = current_pos + motion;
        trenches.push_back(current_pos);
        boundary_point += plan.length;
    }
    
    // calculate the area using the shoelace formula
    long long shoelace_sum = 0;
    int n = trenches.size();
    for(int i = 0; i < n; i++)
    {
        const Point& a = trenches[i]; // get current point
        const Point& b = trenches[(i + 1) % n]; // get next point and loop back to the start
        shoelace_sum += a.row * b.column - a.column * b.row;
    }

    // apply Pick's Theorem to find the number of interior points
    long long area = std::llabs(shoelace_sum);
    long long result = (area + boundary_point) / 2 + 1;

    return std::to_string(result);
}

int main() {

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    std::string p1 = part_one();
    std::string p2 = part_two();

    std::cout << std::endl;
    std::cout << "Part One: " << p1 << std::endl;
    std::cout << std::endl;
    std::cout << "Part Two: " << p2 << std::endl;

    auto stop = high_resolution_clock::now();
    auto dura = duration_cast<milliseconds>(stop - start);
    std::cout << "Execution Time: " << dura.count() << " ms." << std::endl;

    return 0;
}
