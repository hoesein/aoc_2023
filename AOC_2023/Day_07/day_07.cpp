#include <algorithm>
#include "../common.h"

bool five(const std::vector<char> &h)
{
    for (int i = 0; i < h.size(); i++)
    {
        if (h[i] != h[0])
            return false;
    }
    return true;
}

bool four(const std::vector<char> &h)
{
    std::map<char, int> f;
    for (int i = 0; i < h.size(); i++)
    {
        if (f.find(h[i]) == f.end())
        {
            f[h[i]] = 1;
        }
        else
        {
            f[h[i]]++;
        }
        if (f[h[i]] == 4)
            return true;
    }
    if (f[h[h.size() - 1]] == 4)
        return true;
    return false;
}

bool full_house(const std::vector<char> &h)
{
    std::map<char, int> f;
    for (int i = 0; i < h.size(); i++)
    {
        if (f.find(h[i]) == f.end())
        {
            f[h[i]] = 1;
        }
        else
        {
            f[h[i]]++;
        }
    }
    if (f.size() != 2)
        return false;

    bool is_two = false;
    bool is_three = false;

    for (auto i = f.cbegin(); i != f.cend(); i++)
    {
        if (i->second == 2)
            is_two = true;
        else if (i->second == 3)
            is_three = true;
    }

    return is_two && is_three;
}

bool three(const std::vector<char> &h)
{
    std::map<char, int> f;
    for (int i = 0; i < h.size(); i++)
    {
        if (f.find(h[i]) == f.end())
        {
            f[h[i]] = 1;
        }
        else
        {
            f[h[i]]++;
        }
        if (f[h[i]] == 3)
            return true;
    }
    if (f[h[h.size() - 1]] == 3)
        return true;
    return false;
}

bool two_pairs(const std::vector<char> &h)
{
    std::map<char, int> f;
    for (int i = 0; i < h.size(); i++)
    {
        if (f.find(h[i]) == f.end())
        {
            f[h[i]] = 1;
        }
        else
        {
            f[h[i]]++;
        }
    }
    int pair_count = 0;
    for (auto i = f.cbegin(); i != f.cend(); i++)
    {
        if (i->second != 1)
            pair_count++;
    }
    return pair_count == 2;
}

bool one_pairs(const std::vector<char> &h)
{
    std::map<char, int> f;
    for (int i = 0; i < h.size(); i++)
    {
        if (f.find(h[i]) == f.end())
        {
            f[h[i]] = 1;
        }
        else
        {
            f[h[i]]++;
        }
    }
    int pair_count = 0;
    for (auto i = f.cbegin(); i != f.cend(); i++)
    {
        if (i->second != 1)
            pair_count++;
    }
    return pair_count == 1;
}

bool high(const std::vector<char> &h)
{
    std::map<char, int> f;
    for (int i = 0; i < h.size(); i++)
    {
        if (f.find(h[i]) == f.end())
        {
            f[h[i]] = 1;
        }
        else
        {
            f[h[i]]++;
        }
    }
    for (auto i = f.cbegin(); i != f.cend(); i++)
    {
        if (i->second != 1)
            return false;
    }
    return true;
}

std::pair<int, std::vector<char>> rank_hand(const std::vector<char> &hand)
{
    if (five(hand))
        return std::make_pair(7, hand);
    else if (four(hand))
        return std::make_pair(6, hand);
    else if (full_house(hand))
        return std::make_pair(5, hand);
    else if (three(hand))
        return std::make_pair(4, hand);
    else if (two_pairs(hand))
        return std::make_pair(3, hand);
    else if (one_pairs(hand))
        return std::make_pair(2, hand);
    else if (high(hand))
        return std::make_pair(1, hand);
    else
        return std::make_pair(0, hand);
}

struct Hand
{
    double bid;
    std::vector<char> hand;

    Hand(double &_bid, const std::vector<char> &_hand) : bid(_bid), hand(_hand) {}

    bool operator<(const Hand &other_hand) const
    {
        int hand_rank = rank_hand(hand).first;
        int other_hand_rank = rank_hand(other_hand.hand).first;

        if (hand_rank != other_hand_rank)
        {
            return hand_rank < other_hand_rank;
        }
        else
        {
            for(int i = 0; i < hand.size(); i++)
            {
                if(hand[i] == other_hand.hand[i]) continue;
                else return hand[i] < other_hand.hand[i];
            }
            return false;
        }
    }
};

std::vector<std::string> read_file()
{
    std::ifstream input_file("D:\\Aung Hein Soe\\Danger\\C++\\AOC_2023\\AOC_2023\\Day_07\\input.txt");
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
    }

    std::map<char, char> replace_char;
    std::vector<char> chars = {'A', 'K', 'Q', 'J', 'T'};
    for (int i = 0; i < chars.size(); i++)
    {
        replace_char[chars[i]] = (char)('9' + (chars.size() - i));
    }

    std::vector<Hand> hands;
    std::vector<std::string> input;
    for (int i = 0; i < lines.size(); i++)
    {
        std::vector<char> hand;
        double bid = 0;

        input = tools::separator(lines[i], " ");
        
        for (const auto &hh : input[0])
        {
            hand.push_back(isdigit(hh) ? hh : replace_char[hh]);
        }
        bid = std::stod(input[1]);

        Hand new_hand = Hand(bid, hand);
        hands.push_back(new_hand);
    }

    std::sort(hands.begin(), hands.end());
    int result = 0;
    for(int i = 0; i < hands.size(); i++)
    {
        Hand h = hands[i];
        result += h.bid * (i + 1);
    }

    return std::to_string(result);
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
