#include "../common.h"
#include <cassert>

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
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }
    int sr, sc;
    for (size_t i = 0; i < lines.size(); i++)
    {
        bool lb = false;
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == 'S')
            {
                sr = i;
                sc = j;
                lb = true;
                break;
            }
            if (lb)
                break;
        }
    }
    std::set<std::pair<int, int>> seen;
    seen.insert(std::make_pair(sr, sc));

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(sr, sc));

    while (!q.empty())
    {
        std::pair<int, int> curr_pos = q.front();
        q.pop();
        int r = curr_pos.first;
        int c = curr_pos.second;
        char curr_ch = lines[r][c];

        // check previous row
        auto &prch = lines[r - 1][c];
        if (r > 0 && (curr_ch == 'S' || curr_ch == 'L' || curr_ch == 'J' || curr_ch == '|') && (lines[r - 1][c] == '|' || lines[r - 1][c] == '7' || lines[r - 1][c] == 'F') && seen.find(std::make_pair(r - 1, c)) == seen.end())
        {
            seen.insert(std::make_pair(r - 1, c));
            q.push(std::make_pair(r - 1, c));
        }

        // check next row
        auto &nrch = lines[r + 1][c];
        if (r < lines.size() && (curr_ch == 'S' || curr_ch == '|' || curr_ch == '7' || curr_ch == 'F') && (lines[r + 1][c] == '|' || lines[r + 1][c] == 'J' || lines[r + 1][c] == 'L') && seen.find(std::make_pair(r + 1, c)) == seen.end())
        {
            seen.insert(std::make_pair(r + 1, c));
            q.push(std::make_pair(r + 1, c));
        }

        // check left column
        auto &lcch = lines[r][c - 1];
        if (c > 0 && (curr_ch == 'S' || curr_ch == '-' || curr_ch == 'J' || curr_ch == '7') && (lines[r][c - 1] == '-' || lines[r][c - 1] == 'L' || lines[r][c - 1] == 'F') && seen.find(std::make_pair(r, c - 1)) == seen.end())
        {
            seen.insert(std::make_pair(r, c - 1));
            q.push(std::make_pair(r, c - 1));
        }

        // check right column
        auto &rcch = lines[r][c + 1];
        if (c < lines[r].size() && (curr_ch == 'S' || curr_ch == '-' || curr_ch == 'L' || curr_ch == 'F') && (lines[r][c + 1] == '-' || lines[r][c + 1] == 'J' || lines[r][c + 1] == '7') && seen.find(std::make_pair(r, c + 1)) == seen.end())
        {
            seen.insert(std::make_pair(r, c + 1));
            q.push(std::make_pair(r, c + 1));
        }
    }

    // for (const auto &s : seen)
    // {
    //     std::cout << s.first << " and " << s.second << std::endl;
    // }

    return std::to_string(seen.size() / 2);
}

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::string> graph = lines;
    int sr, sc;
    for (size_t r = 0; r < graph.size(); r++)
    {
        bool lb = false;
        for (size_t c = 0; c < graph[r].size(); c++)
        {
            if (lines[r][c] == 'S')
            {
                sr = r;
                sc = c;
                lb = true;
                break;
            }
            if (lb)
                break;
        }
    }

    std::set<std::pair<int, int>> loop;
    loop.insert(std::make_pair(sr, sc));

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(sr, sc));

    std::set<char> possibleS;
    possibleS.insert('|');
    possibleS.insert('-');
    possibleS.insert('J');
    possibleS.insert('L');
    possibleS.insert('7');
    possibleS.insert('F');

    while (!q.empty())
    {
        std::pair<int, int> curr_pos = q.front();
        q.pop();

        int r = curr_pos.first;
        int c = curr_pos.second;
        char curr_ch = graph[r][c];

        // check up row
        if (r > 0 && (curr_ch == 'S' || curr_ch == '|' || curr_ch == 'J' || curr_ch == 'L') && (graph[r - 1][c] == '|' || graph[r - 1][c] == '7' || graph[r - 1][c] == 'F') && loop.find(std::make_pair(r - 1, c)) == loop.end())
        {
            loop.insert(std::make_pair(r - 1, c));
            q.push(std::make_pair(r - 1, c));
            if (curr_ch == 'S')
            {
                std::set<char> copy_set = possibleS;
                for (auto it = copy_set.begin(); it != copy_set.end(); ++it)
                {
                    if (*it != '|' && *it != 'J' && *it != 'L')
                    {
                        possibleS.erase(*it);
                    }
                }
            }
        }

        // check down row
        if (r < lines.size() && (curr_ch == 'S' || curr_ch == '|' || curr_ch == '7' || curr_ch == 'F') && (lines[r + 1][c] == '|' || lines[r + 1][c] == 'J' || lines[r + 1][c] == 'L') && loop.find(std::make_pair(r + 1, c)) == loop.end())
        {
            loop.insert(std::make_pair(r + 1, c));
            q.push(std::make_pair(r + 1, c));
            if (curr_ch == 'S')
            {
                std::set<char> copy_set = possibleS;
                for (auto it = copy_set.begin(); it != copy_set.end(); ++it)
                {
                    if (*it != '|' && *it != '7' && *it != 'F')
                    {
                        possibleS.erase(*it);
                    }
                }
            }
        }

        // check left column
        auto &lcch = lines[r][c - 1];
        if (c > 0 && (curr_ch == 'S' || curr_ch == '-' || curr_ch == 'J' || curr_ch == '7') && (lines[r][c - 1] == '-' || lines[r][c - 1] == 'L' || lines[r][c - 1] == 'F') && loop.find(std::make_pair(r, c - 1)) == loop.end())
        {
            loop.insert(std::make_pair(r, c - 1));
            q.push(std::make_pair(r, c - 1));

            if (curr_ch == 'S')
            {
                std::set<char> copy_set = possibleS;
                for (auto it = copy_set.begin(); it != copy_set.end(); ++it)
                {
                    if (*it != '-' && *it != 'J' && *it != '7')
                    {
                        possibleS.erase(*it);
                    }
                }
            }
        }

        // check right column
        auto &rcch = lines[r][c + 1];
        if (c < lines[r].size() && (curr_ch == 'S' || curr_ch == '-' || curr_ch == 'L' || curr_ch == 'F') && (lines[r][c + 1] == '-' || lines[r][c + 1] == 'J' || lines[r][c + 1] == '7') && loop.find(std::make_pair(r, c + 1)) == loop.end())
        {
            loop.insert(std::make_pair(r, c + 1));
            q.push(std::make_pair(r, c + 1));

            if (curr_ch == 'S')
            {
                std::set<char> copy_set = possibleS;
                for (auto it = copy_set.begin(); it != copy_set.end(); ++it)
                {
                    if (*it != '-' && *it != 'L' && *it != 'F')
                    {
                        possibleS.erase(*it);
                    }
                }
            }
        }
    }

    // unknown signal error
    assert(possibleS.size() == 1);
    char S = *possibleS.begin();

    graph[sr] = graph[sr].substr(0, sc) + S + graph[sr].substr(sc + 1, graph[sr].size() - sc);

    std::vector<std::vector<char>> new_graph;
    for (int r = 0; r < graph.size(); r++)
    {
        std::vector<char> curr_row;
        for (int c = 0; c < graph[r].size(); c++)
        {
            if (loop.find(std::make_pair(r, c)) == loop.end())
                curr_row.push_back('.');
            else
                curr_row.push_back(graph[r][c]);
        }
        new_graph.push_back(curr_row);
    }

    std::set<std::pair<int, int>> outside;
    for (int r = 0; r < new_graph.size(); r++)
    {
        bool within = false;
        bool up = false;
        for (int c = 0; c < new_graph[r].size(); c++)
        {
            char ch = new_graph[r][c];
            if (ch == '|')
                within = !within;
            else if (ch == 'F' || ch == 'L')
                up = (ch == 'L');
            else if (ch == '7' || ch == 'J')
            {
                if (up)
                {
                    if (ch != 'J')
                        within = !within;
                }
                else
                {
                    if (ch != '7')
                        within = !within;
                }
                up = false;
            }
            if (!within)
                outside.insert(std::make_pair(r, c));
        }
    }
    std::set<std::pair<int, int>> outside_union_loop;
    std::set_union(outside.begin(), outside.end(), loop.begin(), loop.end(), std::inserter(outside_union_loop, outside_union_loop.begin()));
    std::cout << new_graph.size() << " " << new_graph[0].size() << " " << outside.size() << " " << loop.size() << std::endl;

    return std::to_string(new_graph.size() * new_graph[0].size() - outside_union_loop.size());
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
