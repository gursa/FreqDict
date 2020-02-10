#include "freq.hpp"

#include <algorithm>
#include <exception>
#include <locale>
#include <unordered_map>
#include <utility>

TFreq::TFreq(const std::string& input) {
    std::ifstream InputFile(input);
    if (!InputFile.is_open()) {
        std::runtime_error("Couldn't open input file" + input);
    }

    ReadData(InputFile);

    InputFile.close();
}

TFreq::TFreq(std::istream& input) {
    ReadData(input);
}

void TFreq::ReadData(std::istream& input) {
    std::string KeyName;
    std::unordered_map<std::string, size_t> Dictionary;
    for (TFileIterator Symbol(input), end; Symbol != end; ++Symbol) {
        if (std::isalpha(*Symbol, std::locale::classic())) {
            KeyName.append(1, std::tolower(*Symbol, std::locale::classic()));
        } else {
            if (!KeyName.empty()) {
                Dictionary[KeyName]++;
            }
            KeyName.clear();
        }
    }

    if (!KeyName.empty()) {
        Dictionary[KeyName]++;
    }

    for (auto& [TextWord, Count] : Dictionary) {
        Data.push_back(std::make_pair(Count, TextWord));
    }
}

void TFreq::SaveData(const std::string& output) {
    std::ofstream OutputFile(output);
    if (!OutputFile.is_open()) {
        std::runtime_error("Couldn't open output file" + output);
    }

    for (auto& Item : Data) {
        OutputFile << Item.first << "\t" << Item.second << std::endl;
    }

    OutputFile.close();
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
