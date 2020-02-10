#include "freq.h"

#include <algorithm>
#include <exception>
#include <locale>
#include <unordered_map>
#include <utility>

void TFreq::ReadData(const std::string &input)
{
    std::ifstream InputFile(input);
    if(!InputFile.is_open()) {
        std::runtime_error("Couldn't open input file" + input);
    }

    std::locale loc;
    std::string keyName;
    std::unordered_map<std::string, size_t> Dictionary;
    for(TFileIterator symbol(InputFile), end; symbol != end; ++symbol){
        if(std::isalpha(*symbol, loc)) {
            keyName.append(1, std::tolower(*symbol, loc));
        } else {
            if(!keyName.empty()) {
                Dictionary[keyName]++;
            }
            keyName.clear();
        }
    }
    InputFile.close();

    if(!keyName.empty()) {
        Dictionary[keyName]++;
    }

    for(auto& [key, value]: Dictionary) {
        Data.push_back(std::make_pair(value, key));
    }
}

void TFreq::SortData()
{
    std::sort(Data.begin(), Data.end(), [](const auto& lhs, const auto& rhs) {
        if(lhs.first > rhs.first) {
            return true;
        }
        if(lhs.first < rhs.first) {
            return false;
        }

        if(lhs.second < rhs.second) {
            return true;
        }

        return false;
    });
}

void TFreq::SaveData(const std::string &output)
{
    std::ofstream OutputFile(output);
    if(!OutputFile.is_open()) {
        std::runtime_error("Couldn't open output file" + output);
    }

    for(auto& item: Data) {
        OutputFile << item.first << "\t" << item.second << std::endl;
    }

    OutputFile.close();
}

void TFreq::Analyze(const std::string &input, const std::string &output)
{
    ReadData(input);
    SortData();
    SaveData(output);
}
