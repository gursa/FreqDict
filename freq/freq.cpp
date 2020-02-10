#include "freq.hpp"

#include <algorithm>
#include <exception>
#include <locale>
#include <unordered_map>
#include <utility>

TFreq::TFreq(const std::string& inputFilename) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::runtime_error("Couldn't open input file" + inputFilename);
    }

    ReadData(inputFile);
}

TFreq::TFreq(std::istream& inputStream) {
    ReadData(inputStream);
}

void TFreq::ReadData(std::istream& inputStream) {
    std::string keyName;
    std::unordered_map<std::string, size_t> dictionary;
    for (TFileIterator symbol(inputStream), end; symbol != end; ++symbol) {
        if (std::isalpha(*symbol, std::locale::classic())) {
            keyName.append(1, std::tolower(*symbol, std::locale::classic()));
        } else {
            if (!keyName.empty()) {
                dictionary[keyName]++;
            }
            keyName.clear();
        }
    }

    if (!keyName.empty()) {
        dictionary[keyName]++;
    }

    Data.reserve(dictionary.size());

    for (auto& [textWord, count] : dictionary) {
        Data.emplace_back(count, textWord);
    }
}

void TFreq::SaveData(const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::runtime_error("Couldn't open output file" + outputFilename);
    }

    for (auto& item : Data) {
        outputFile << item.first << "\t" << item.second << std::endl;
    }
}

void TFreq::Analyze() {
    std::sort(Data.begin(), Data.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.first > rhs.first) {
            return true;
        }

        if (lhs.first < rhs.first) {
            return false;
        }

        if (lhs.second < rhs.second) {
            return true;
        }

        return false;
    });
}
