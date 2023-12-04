#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>

const bool DEBUG = false;


int getCount(const std::string& inputString) {
    if (DEBUG) {
        std::cout << "\t \t inputString = " << inputString << std::endl;
    }
    std::string charDigits = "0123456789";
    int num = 0;
    std::string::size_type pos_first = inputString.find_first_of(charDigits);
    if (pos_first == std::string::npos) {
        return num;
    }
    std::string::size_type pos_last = inputString.find_last_of(charDigits);
    int factor = 0;
    for (int index = pos_last; index >= pos_first ; --index) {
        int digit = inputString[index] - '0';
        num += (digit * pow(10, factor));
        ++factor;
    }
    if (DEBUG) {
        std::cout << "\t \t num found = " << num << std::endl;
    }
    return num;
}

std::string getColor(const std::string& ballInfo, const std::vector<std::string>& colorCodes) {
    std::string colorFound = "";
    for (const auto& color : colorCodes) {
        if (ballInfo.find(color) != std::string::npos) {
            colorFound = color;
        }
    }
    if (DEBUG) {
        std::cout << "\t \t color found = " << colorFound << std::endl;
    }
    return colorFound;
}

std::vector<std::string> getSubStrings(const std::string& inputString, const std::string& delimiter) {
    std::vector<std::string> delimitedStrings;
    std::string stringToParse = inputString;
    while (stringToParse.length() > 0) {
        std::string::size_type pos = stringToParse.find_last_of(delimiter);
        if (pos == std::string::npos) {
            delimitedStrings.push_back(stringToParse);
            break;
        }
        delimitedStrings.push_back(stringToParse.substr(pos + 1));
        stringToParse = stringToParse.substr(0, pos);
    }
    if (DEBUG) {
        std::cout << "\n \t Input string: " << inputString << std::endl;
        std::cout << "\t Strings parsed for " << delimiter << " are:" << std::endl;
        for (const auto& substr : delimitedStrings) {
            std::cout << "\t \t" << substr << std::endl;
        }
    }
    return delimitedStrings;
}


int main (int argc, char** argv) {

    std::filesystem::path inputFile = "day2_input.txt";
    if (!std::filesystem::exists(inputFile)) {
        std::cerr << "Input file " << inputFile.string() << " does not exist!" << std::endl;
        return -1;
    }
    std::ifstream inputFileStream(inputFile.string());
    std::string line;
    std::map<std::string, int> BALL_INFO;
    BALL_INFO["blue"] = 14;
    BALL_INFO["red"] = 12;
    BALL_INFO["green"] = 13;
    std::vector<std::string> colorCodes(3);
    colorCodes[0] = "blue";
    colorCodes[1] = "green";
    colorCodes[2] = "red";
    int sum = 0;
    while (std::getline(inputFileStream, line)) {
        std::string::size_type delimIndex = line.find(':');
        std::string gameRoundsInfo = line.substr(delimIndex + 1);
        std::string gameId = line.substr(0, delimIndex);
        if (DEBUG) {
            std::cout << "Evaluating " << gameId << " for " << gameRoundsInfo << std::endl;
        }
        std::string gameRoundDelimiter = ";";
        std::vector<std::string> gameRounds = getSubStrings(gameRoundsInfo, gameRoundDelimiter);
        bool possibleGameRound = true;
        for (int roundId = 0; roundId < gameRounds.size(); ++roundId) {
            std::string ballInfoDelimiter = ",";
            std::vector<std::string> ballInfos = getSubStrings(gameRounds[roundId], ballInfoDelimiter);
            bool possible = true;
            for (int infoId = 0; infoId < ballInfos.size(); ++infoId) {
                int ballCount = getCount(ballInfos[infoId]);
                std::string ballColor = getColor(ballInfos[infoId], colorCodes);
                if (ballColor.empty()) {
                    continue;
                }
                if (ballCount > BALL_INFO[ballColor]) {
                    possible &= false;
                }
            }
            possibleGameRound &= possible;
            if (DEBUG) {
                std::cout << "\t Game round is possible = " << possibleGameRound << std::endl;
            }
        }
        int gameCount = getCount(gameId);
        if (DEBUG) {
            std::cout << "Game " << gameCount << " is possible = " << possibleGameRound << std::endl;
        }
        if (possibleGameRound) {
            sum += gameCount;
        }
    }
    std::cout << "Sum of all the possible game ids = " << sum << std::endl;
    return 0;
}
