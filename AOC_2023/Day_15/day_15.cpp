#include "../common.h"

/*
 * Part One: requirement
 * set current value to 0
 * change first letter of char to ASCII value
 * then multiply by 17
 * then get remainder of divided by 256
 */

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

int HASH(const std::string &str)
{
    int value = 0;
    for (char c : str)
    {
        value = ((value + static_cast<int>(c)) * 17) % 256;
    }
    return value;
}

std::string part_one()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::string> separated_lines;
    for (const auto &line : lines)
    {
        auto separated = tools::separator(line, ",");
        separated_lines.insert(separated_lines.end(), separated.begin(), separated.end());
    }

    int result = 0;
    for (const auto &separated_line : separated_lines)
    {
        std::string word = separated_line;
        tools::trim(word);
        if (word.empty())
            continue;

        result += HASH(word);
        // std::cout << "Value for '" << word << "': " << HASH(word) << std::endl;
    }

    return std::to_string(result);
}

struct Lens
{
    std::string label;
    int focal_length;
};

std::string part_two()
{
    std::vector<std::string> lines = read_file();
    if (lines.empty())
    {
        std::cerr << "No data found." << std::endl;
        return 0;
    }

    std::vector<std::string> separated_lines;
    for (const auto &line : lines)
    {
        auto separated = tools::separator(line, ",");
        separated_lines.insert(separated_lines.end(), separated.begin(), separated.end());
    }

    std::vector<std::vector<Lens>> boxes(256);
    for (const auto &separated_line : separated_lines)
    {
        std::string word = separated_line;
        tools::trim(word);
        if (word.empty())
            continue;

        if (word.find("=") != std::string::npos)
        {
            // add or update lens
            size_t pos = word.find("=");
            std::string label = word.substr(0, pos);
            int focal_length = std::stoi(word.substr(pos + 1));
            int box_index = HASH(label);

            // if already in box, update lens
            bool found = false;
            for (auto &lens : boxes[box_index])
            {
                if (lens.label == label)
                {
                    lens.focal_length = focal_length;
                    found = true;
                    break;
                }
            }

            // add as new lens to box
            if (!found)
            {
                boxes[box_index].push_back({label, focal_length});
            }
        }
        else if (word.find("-") != std::string::npos)
        {
            // remove lens
            size_t pos = word.find("-");
            std::string label = word.substr(0, pos);
            int box_index = HASH(label);

            boxes[box_index].erase(
                std::remove_if(boxes[box_index].begin(), boxes[box_index].end(),
                               [&label](const Lens &lens)
                               { return lens.label == label; }),
                boxes[box_index].end());
        }
    }

    int result = 0;
    for (int box_num = 0; box_num < boxes.size(); box_num++)
    {
        for (int slot = 0; slot < boxes[box_num].size(); slot++)
        {
            result += (box_num + 1) * (slot + 1) * boxes[box_num][slot].focal_length;
            std::cout << "Box " << box_num + 1 << ", Slot " << slot << ": "
                      << boxes[box_num][slot].label << " (Focal Length: "
                      << boxes[box_num][slot].focal_length << ") -> Result: "
                      << result << std::endl;
        }
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
