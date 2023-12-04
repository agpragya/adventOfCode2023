#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

int main (int argc, char** argv) {

    std::filesystem::path inputFile = "day1_input.txt";
    if (!std::filesystem::exists(inputFile)) {
        std::cerr << "Input file " << inputFile.string() << " does not exist!" << std::endl;
        return -1;
    }
    std::ifstream inputFileStream(inputFile.string());
    std::string line;
    std::string digits = "0123456789";
    int sum = 0;
    while (std::getline(inputFileStream, line)) {
        std::string::size_type first_digit_pos = line.find_first_of(digits);
        if (first_digit_pos == std::string::npos) {
            // no digits in this line
            continue;
        }
        int first_digit = line[first_digit_pos] - '0';
        int second_digit = line[line.find_last_of(digits)] - '0';
        int num = first_digit * 10 + second_digit;
        std::cout << "first_digit = " << first_digit << ", second_digit = " << second_digit << ", num = " << num << std::endl;
        sum += num;
    }

    std::cout << "Sum of all the numbers = " << sum << std::endl;

    return 0;
}
