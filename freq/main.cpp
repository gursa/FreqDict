#include "freq.h"

#include <iostream>

int main(int argc, char* argv[])
{
    try {
        if(argc < 3) {
            std::cerr << "Incorrect number of arguments (" << argc << ")" << std::endl;
            std::cerr << "Usage: ./freq in.txt out.txt" << std::endl;
        }

        TFreq freq;
        freq.Analyze(argv[1], argv[2]);
    } catch (const std::exception& ex) {
        std::cerr << "[Exception] " << ex.what() << std::endl;
    }
    return 0;
}
