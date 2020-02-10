#pragma once

#include <fstream>
#include <vector>


class TFreq
{
using TFileIterator = std::istreambuf_iterator<char>;
using TDataPair = std::pair<size_t, std::string>;

public:
    void Analyze(const std::string& input, const std::string& output);

private:
    void ReadData(const std::string& input);
    void SortData();
    void SaveData(const std::string& output);

private:
    std::vector<TDataPair> Data;
};

