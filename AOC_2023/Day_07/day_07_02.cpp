#include "../common.h"

enum hand_type
{
    HIGHT_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_KIND = 5,
    FIVE_KIND = 6,
};

std::string ttostr(hand_type type)
{
    switch (type)
    {
    case HIGHT_CARD:
        return "High Card";
    case ONE_PAIR:
        return "One Pair";
    case TWO_PAIR:
        return "Two Pair";
    case THREE_KIND:
        return "Three of a kind";
    case FULL_HOUSE:
        return "Full House";
    case FOUR_KIND:
        return "Four of a kind";
    case FIVE_KIND:
        return "Five of a kind";
    default:
        return "Unknow";
    }
}

class CamelHand
{
private:
    std::vector<char> cards;
    int bet;
    hand_type type;
    int rank;
    std::map<char, int> card_strength = {{'J', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 12}, {'K', 13}, {'A', 14}};

    hand_type find_best_type(const std::vector<char> &cards)
    {
        std::map<char, int> card_counts;
        int joker_count = 0;
        for (char c : cards)
        {
            if (c == 'J')
            {
                joker_count++;
            }
            else
            {
                card_counts[c]++;
            }
        }
        if (joker_count == 5)
            return FIVE_KIND;

        char best_card = card_counts.begin()->first;
        int max_count = 0;
        for (const auto &[card, count] : card_counts)
        {
            if (count > max_count || (count == max_count && card_strength[card] > card_strength[best_card]))
            {
                max_count = count;
                best_card = card;
            }
        }

        card_counts[best_card] += joker_count;

        bool has_three = false;
        int pair_count = 0;
        for (const auto &[card, count] : card_counts)
        {
            if (count == 5)
                return FIVE_KIND;
            if (count == 4)
                return FOUR_KIND;
            if (count == 3)
                has_three = true;
            if (count == 2)
                pair_count++;
        }
        if (has_three && pair_count == 1)
            return FULL_HOUSE;
        if (has_three)
            return THREE_KIND;
        if (pair_count == 2)
            return TWO_PAIR;
        if (pair_count == 1)
            return ONE_PAIR;
        return HIGHT_CARD;
    }
    void determine_type()
    {
        type = find_best_type(cards);
    }

public:
    CamelHand(const std::vector<char> &cards, int bet) : cards(cards), bet(bet), rank(0)
    {
        determine_type();
    }

    bool operator<(const CamelHand &other_hand) const
    {
        if (type != other_hand.type)
        {
            return type < other_hand.type;
        }

        for (size_t i = 0; i < cards.size(); i++)
        {
            int this_strength = card_strength.at(cards[i]);
            int other_strength = card_strength.at(other_hand.cards[i]);
            if (this_strength != other_strength)
            {
                return this_strength < other_strength;
            }
        }
        return false;
    }

    // Getters
    std::vector<char> get_cards() const { return cards; }
    int get_bet() const { return bet; }
    hand_type get_type() const { return type; }
    int get_rank() const { return rank; }

    // Setters
    void set_rank(int new_rank) { rank = new_rank; }

    // For Printing
    friend std::ostream &operator<<(std::ostream &os, const CamelHand &hand)
    {
        std::string str(hand.cards.begin(), hand.cards.end());

        os << "Hand: " << str << " | Bet: " << hand.bet << " | Type: " << ttostr(hand.type) << " | Rank: " << hand.rank;
        return os;
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

int main()
{
    std::vector<std::string> lines = read_file();
    std::vector<std::string> line;
    std::vector<CamelHand> camel_hands;

    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<char> hand;
        line = tools::separator(lines[i], " ");        
        for(size_t j = 0; j < line[0].size(); j++)
        {
            hand.push_back(line[0][j]);
        }
        
        camel_hands.push_back({hand, std::stoi(line[1])});
    }
    
    std::sort(camel_hands.begin(), camel_hands.end());

    for(size_t i = 0; i < camel_hands.size(); i++)
    {
        camel_hands[i].set_rank(i + 1);
    }

    int result = 0;
    for(const auto& hand: camel_hands)
    {
        result += hand.get_bet() * hand.get_rank();
        std::cout << hand << std::endl;
    }
    std::cout << "Final result is: " << std::to_string(result) << std::endl;
    return 0;
}