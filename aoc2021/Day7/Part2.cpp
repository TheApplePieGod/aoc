#include <iostream>
#include <array>
#include <unordered_map>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

std::unordered_map<u64, u64> sumCache;

u64 sum(u64 num)
{
    if (sumCache.find(num) != sumCache.end())
        return sumCache[num];

    if (num == 1)
        return 1;
    if (num == 0)
        return 0;

    u64 val = num + sum(num - 1);;
    sumCache[num] = val;
    return val;
}

int main()
{
    Timer timer("Day7Part2");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day7/input.txt");
    std::vector<int> positions = StringUtils::SplitToInt(lines[0], ",");
    
    int minPos = 99999999;
    int maxPos = 0;
    for (int pos : positions)
    {
        if (pos < minPos) minPos = pos;
        if (pos > maxPos) maxPos = pos;
    }

    u64 minFuel = std::numeric_limits<u64>().max();
    for (int i = minPos; i <= maxPos; i++)
    {
        u64 fuel = 0;
        for (int pos : positions)
            fuel += sum(abs(pos - i));
        if (fuel < minFuel) minFuel = fuel;
    }

    std::cout << "Min fuel: " << minFuel << std::endl;

    return 0;
}