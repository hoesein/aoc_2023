#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <map>
#include <algorithm>
#include <numeric>

namespace tools
{
    bool contain(std::string word, std::string separator)
    {
        int result = word.find(separator);
        if ((result >= 0) && (result <= word.length()))
        {
            return true;
        }
        else if (result == std::string::npos)
        {
            return false;
        }
        else
        {
            return false;
        }
    }

    std::vector<std::string> separator(std::string input, std::string separator = ",")
    {
        std::vector<std::string> separated_string = {};
        std::string word;

        if (separator.length() == 1)
        {
            std::istringstream split(input);

            // for (std::string each; std::getline(split, each, separator[0]); separated_string.push_back(each));

            std::string each;
            while (std::getline(split, each, separator[0]))
            {
                separated_string.push_back(each);
            }

            if (separated_string.empty())
            {
                if (separated_string.back().back() == separator[0])
                {
                    separated_string.back().pop_back();
                }
            }
        }
        else
        {
            for (int i = 0; i < input.length(); i++)
            {
                word += input[i];
                if (contain(word, separator))
                {
                    word.erase(word.find(separator), separator.length());
                    separated_string.push_back(word);
                    word.clear();
                }
            }
            separated_string.push_back(word);
        }
        return separated_string;
    }

    template <typename T>
    T convert(const std::string &str);

    template <>
    std::string convert<std::string>(const std::string &str)
    {
        return str;
    }

    template <>
    int convert<int>(const std::string &str)
    {
        return std::stoi(str);
    }

    template <>
    double convert<double>(const std::string &str)
    {
        return std::stod(str);
    }

    template <>
    uint64_t convert<uint64_t>(const std::string &str)
    {
        return std::stoull(str);
    }

    template <>
    long long convert<long long>(const std::string &str)
    {
        return std::stoull(str);
    }

    template <typename T>
    std::vector<T> remove(std::string input, char delimiter = ' ')
    {
        std::vector<T> tokens;

        std::istringstream ss(input);

        std::string each;
        while (std::getline(ss, each, delimiter))
        {
            if (!each.empty())
            {
                tokens.push_back(convert<T>(each));
            }
        }

        // for (std::string each; std::getline(ss, each, delimiter); tokens.push_back(std::stoi(each)));

        return tokens;
    }

    inline void rtrim(std::string &str)
    {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch)
                                            { return !std::isspace(ch) && ch != '(' && ch != ')'; }));
    }

    inline void ltrim(std::string &str)
    {
        str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch)
                               { return !std::isspace(ch) && ch != '(' && ch != ')'; })
                      .base(),
                  str.end());
    }

    inline void trim(std::string &str)
    {
        rtrim(str);
        ltrim(str);
    }
}