#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <cctype>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file_name>\n";
        return 1;
    }

    std::string file_name = argv[1];

    // Captialize the first letter of the file name for folder name
    std::string folder_name = file_name;
    std::transform(folder_name.begin(), folder_name.begin() + 1, folder_name.begin(), ::toupper);
    
    std::string cpp_path = folder_name + "/" + file_name + ".cpp";
    std::string test_path = folder_name + "/test.txt";
    std::string input_path = folder_name + "/input.txt";

    if (!std::filesystem::exists(folder_name))
    {
        std::filesystem::create_directory(folder_name);
    }

    std::ofstream cpp_file(cpp_path);
    if (!cpp_file)
    {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::ifstream sample_file("sample.txt");
    if (!sample_file.is_open())
    {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;
    while (std::getline(sample_file, line))
    {
        cpp_file << line << "\n";
    }

    sample_file.close();
    cpp_file.close();

    std::ofstream test_txt(test_path);
    std::ofstream input_txt(input_path);

    std::cout << "Generated: " << file_name << ".cpp\n";
    std::cout << "Generated: test.txt\n";
    std::cout << "Generated: input.txt\n";
    return 0;
}
