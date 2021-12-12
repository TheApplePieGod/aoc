#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

int main()
{
    Timer timer("Day6Part2");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day6/input.txt");
    std::vector<int> intitialCounts = StringUtils::SplitToInt(lines[0], ",");

    std::array<u64, 9> dayCounts{}; // 0 1 2 3 4 5 6 7 8
    for (int count : intitialCounts)
        dayCounts[count]++;        

    for (int day = 0; day < 256; day++)
    {
        u64 add = dayCounts[0];
        for (int i = 0; i < dayCounts.size() - 1; i++)
            dayCounts[i] = dayCounts[i + 1];
        dayCounts[6] += add;
        dayCounts[8] = add;
    }

    u64 total = 0;
    for (u64 count : dayCounts)
        total += count;

    std::cout << "Count: " << total << std::endl;

    return 0;
}