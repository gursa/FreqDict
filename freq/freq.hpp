#pragma once

#include <iterator>
#include <fstream>
#include <vector>


class TFreq {
    using TFileIterator = std::istreambuf_iterator<char>;
    using TDataPair = std::pair<size_t, std::string>;

public:
    explicit TFreq(const std::string& inputFilename);
    explicit TFreq(std::istream& inputStream);
    void Analyze();
    void SaveData(const std::string& outputFilename);

    TFreq(const TFreq&) = delete;
    const TFreq& operator=(const TFreq&) = delete;

private:
    void ReadData(std::istream& input);
    void SortData();

private:
    std::vector<TDataPair> Data;
};
