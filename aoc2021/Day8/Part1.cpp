#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

struct Entry
{
    std::vector<std::string> SignalPatterns;
    std::vector<std::string> OutputValues;
};

int main()
{
    Timer timer("Day8Part1");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day8/input.txt");
    
    // parse
    std::vector<Entry> entries;
    for (auto& line : lines)
    {
        auto split = StringUtils::Split(line, " | ");
        entries.push_back({
            StringUtils::Split(split[0], " "),
            StringUtils::Split(split[1], " ")
        });
    }

    int count = 0;
    for (auto& entry : entries)
        for (auto& val : entry.OutputValues)
            if (val.size() == 2 || val.size() == 4 || val.size() == 3 || val.size() == 7)
                count++;

    std::cout << "Counts: " << count << std::endl;

    return 0;
}