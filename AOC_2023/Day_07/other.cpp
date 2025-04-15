#include "../common.h"

enum hand_type
{
    HIGHT_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_KIND = 5,
    FIVE_KIND = 6
};

std::string hand_type_to_string(hand_type type)
{
    switch(type)
    {
        case HIGHT_CARD: return "High Card";
        case ONE_PAIR: return "One Pair";
        case TWO_PAIR: return "Two Pair";
        case THREE_KIND: return "Three of a kind";
        case FULL_HOUSE: return "Full House";
        case FOUR_KIND: return "Four of a kind";
        case FIVE_KIND: return "Five of a kind";
        default: return "Unknow";
    }
}

class CamelHand
{
private:
    std::vector<char> _cards;
    int _bet;
    hand_type _type;
    int _rank;

    std::map<char, int> card_strength = {{'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};
    
    void determine_type()
    {
        std::map<char, int> card_counts;
        for (char c : _cards)
        {
            card_counts[c]++;
        }
        bool has_three = false;
        int pair_count = 0;

        for (const auto &[card, count] : card_counts)
        {
            if (count == 5)
            {
                _type = FIVE_KIND;
                return;
            }
            if (count == 4)
            {
                _type = FOUR_KIND;
                return;
            }
            if (count == 3)
            {
                has_three = true;
            }
            if (count == 2)
            {
                pair_count++;
            }
        }

        if (has_three && pair_count == 1)
        {
            _type = FULL_HOUSE;
        }
        else if (has_three)
        {
            _type = THREE_KIND;
        }
        else if (pair_count == 2)
        {
            _type = TWO_PAIR;
        }
        else if (pair_count == 1)
        {
            _type = ONE_PAIR;
        }
        else
        {
            _type = HIGHT_CARD;
        }
    }

public:
    CamelHand(const std::vector<char> &cards, int bet) : _cards(cards), _bet(bet), _rank(0)
    {
        determine_type();
    }

    bool operator<(const CamelHand& other_hand) const 
    {
       if(_type != other_hand._type)
       {
        return _type < other_hand._type;
       } 

       for (size_t i = 0; i < _cards.size(); i++)
       {
            int this_strength = card_strength.at(_cards[i]);
            int other_strength = card_strength.at(other_hand._cards[i]);
            if(this_strength != other_strength)
            {
                return this_strength < other_strength;
            }
       }
       return false;
    }

    // Getters
    std::vector<char> get_cards() const { return _cards; }
    int get_bet() const { return _bet; }
    hand_type get_type() const { return _type; }
    int get_rank() const { return _rank; }

    // Setters
    void set_rank(int new_rank) { _rank = new_rank; }

    // For Printing
    friend std::ostream& operator<<(std::ostream &os, const CamelHand &hand)
    {
        std::string str(hand._cards.begin(), hand._cards.end());

        os << "Hand: " << str << " | Bet: " << hand._bet << " | Type: " << hand_type_to_string(hand._type) << " | Rank: " << hand._rank;
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