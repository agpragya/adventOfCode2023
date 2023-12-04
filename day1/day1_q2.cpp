#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>

const bool DEBUG = false;

void findDigitsWithPositionFromLiterals(
    const std::string& numLiteral,
    const std::vector<std::string>& literalDigits, 
    std::map<std::string::size_type, int>* foundDigitsWithPos) {

    for (int num = 0; num < literalDigits.size(); ++num) {
        for (int index = 0; index < numLiteral.length(); ++index) {
            std::string::size_type pos = numLiteral.find(literalDigits[num], index);
            if (pos != std::string::npos) {
                (*foundDigitsWithPos)[pos] = num;
                index += literalDigits[num].length();
            }
        }
    }
}


void findDigitsWithPositionFromChars(
    const std::string& numLiteral,
    const std::string& charDigits,
    std::map<std::string::size_type, int>* foundDigitsWithPos) {
    std::string::size_type first_digit_pos = numLiteral.find_first_of(charDigits);
    if (first_digit_pos != std::string::npos) {
        (*foundDigitsWithPos)[first_digit_pos] = numLiteral[first_digit_pos] - '0';
    }
    std::string::size_type second_digit_pos = numLiteral.find_last_of(charDigits);
    if (second_digit_pos != std::string::npos) {
        (*foundDigitsWithPos)[second_digit_pos] = numLiteral[second_digit_pos] - '0';
    }
}


int computeNumber(
    const std::map<std::string::size_type, int>& digitsFound) {
    if (digitsFound.empty()) {
        return 0;
    }
    if (DEBUG) {
        std::cout << "Digits found:" << std::endl;
        for (auto it = digitsFound.begin(); it != digitsFound.end(); ++it) {
            std::cout << "\t pos = " << it->first << ", " << it->second << std::endl;
        }
    }
    auto it = digitsFound.begin();
    int first_digit = it->second;
    auto rit = digitsFound.rbegin();
    int second_digit = rit->second;
    int num = first_digit*10 + second_digit;
    std::cout << "\t first_digit = " << first_digit << ", second_digit = " << second_digit << ", num = " << num << std::endl;
    return num;
}


int main (int argc, char** argv) {

    std::filesystem::path inputFile = "day1_input.txt";
    if (!std::filesystem::exists(inputFile)) {
        std::cerr << "Input file " << inputFile.string() << " does not exist!" << std::endl;
        return -1;
    }
    std::ifstream inputFileStream(inputFile.string());
    std::string line;
    std::string charDigits = "0123456789";
    std::vector<std::string> literalDigits;
    literalDigits.push_back("zero");
    literalDigits.push_back("one");
    literalDigits.push_back("two");
    literalDigits.push_back("three");
    literalDigits.push_back("four");
    literalDigits.push_back("five");
    literalDigits.push_back("six");
    literalDigits.push_back("seven");
    literalDigits.push_back("eight");
    literalDigits.push_back("nine");

    int sum = 0;
    while (std::getline(inputFileStream, line)) {

        std::map<std::string::size_type, int> foundDigitsWithPos;
        findDigitsWithPositionFromLiterals(line, literalDigits, &foundDigitsWithPos);
        findDigitsWithPositionFromChars(line, charDigits, &foundDigitsWithPos);
        int num = computeNumber(foundDigitsWithPos);
        sum += num;
    }

    std::cout << "Sum of all the numbers = " << sum << std::endl;

    return 0;
}
